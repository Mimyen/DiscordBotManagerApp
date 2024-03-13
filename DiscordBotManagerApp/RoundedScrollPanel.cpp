#include "RoundedScrollPanel.h"



RoundedScrollPanel::RoundedScrollPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, FunctionCallback callback)
    : m_scrollPosition(0), m_totalContentHeight(0), m_isDragging(false), m_lastMouseY(0), m_isScrollbarHovered(false), m_callback(callback)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Create(parent, wxID_ANY, pos, size, wxTRANSPARENT);
    scrollBarRect = wxRect(0, 0, 0, 0);
}

void RoundedScrollPanel::OnScroll(wxMouseEvent& event) {
    int rotation = event.GetWheelRotation();
    int lineHeight = 20; // Adjust as needed for your scroll speed

    // Calculate new scroll position, preventing underflow or overflow
    m_scrollPosition -= rotation / event.GetWheelDelta() * lineHeight;
    m_scrollPosition = Utils::Clamp(m_scrollPosition, 0, std::max(0, m_totalContentHeight - GetClientSize().y));

    RecalculateLayout(); // Re-layout controls based on new scroll position
}

void RoundedScrollPanel::OnSize(wxSizeEvent& event) {
    RecalculateLayout();
    event.Skip(); // Ensure the event is not blocked
}

void RoundedScrollPanel::RecalculateLayout() {
    int yPos = 0; // Start from the very top

    // Use the full width of the RoundedScrollPanel for each control
    int controlWidth = GetClientSize().x;

    for (auto& control : m_scrollControls) {
        // Update each control's position and size to fill the panel horizontally
        control->SetPosition(wxPoint(0, yPos - m_scrollPosition));
        control->SetSize(wxSize(controlWidth, controlWidth));

        // Move yPos for the next control, placing it directly below the previous one without a gap
        yPos += control->GetSize().y;
    }

    // Adjust the total content height based on the final yPos
    m_totalContentHeight = yPos;

    Refresh(); // Redraw to apply layout changes
}

void RoundedScrollPanel::OnLeftUp(wxMouseEvent& event) {
    wxPoint clickPos = event.GetPosition();

    if (m_isDragging) {
        if (HasCapture()) {
            ReleaseMouse();
        }
        m_isDragging = false;
        Refresh();
        return;
    }
    if (scrollBarRect.Contains(clickPos)) {
        return;
    }
}


void RoundedScrollPanel::OnEraseBackground(wxEraseEvent& event) {
    // Do nothing here. This prevents the background from being erased
    // and reduces flickering.
}

void RoundedScrollPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    PrepareDC(dc);
    Render(dc);
}

void RoundedScrollPanel::Render(wxDC& dc)
{
    // Create a rounded rectangle bitmap and then a region from it
    wxRegion roundedRectRegion = Utils::GetRoundedRegion(dc, GetClientSize(), 15); // Threshold near black to treat as transparent

    // Create a memory DC with the same properties as the paint DC
    wxMemoryDC memDC;

    // Get size of the element
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp = Utils::CreateEmptyBitmap(size);

    // Select the bitmap into the memory DC
    memDC.SelectObject(bmp);

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        gc->Clip(roundedRectRegion);

        // Set blending mode for transparency
        gc->SetCompositionMode(wxCOMPOSITION_OVER);

        // Draw the rounded rectangle outline on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
        gc->SetBrush(wxBrush(wxColour(114, 114, 114, 255))); // Set alpha to 255 (opaque)

        // After the loop for drawing controls
        if (m_totalContentHeight > GetClientSize().y) { // Check if the scrollbar is needed

            int visibleHeight = GetClientSize().y - 4; // 2px offset from both top and bottom
            scrollBarRect.height = visibleHeight * visibleHeight / m_totalContentHeight;
            scrollBarRect.y = 2 + (m_scrollPosition * (visibleHeight - scrollBarRect.height) / (m_totalContentHeight - GetClientSize().y));

            // Determine the scrollbar color based on its state
            wxColour scrollbarColor(255, 255, 255); // White color

            // Create a graphics context for drawing
            gc->SetBrush(wxBrush(wxColour(scrollbarColor.Red(), scrollbarColor.Green(), scrollbarColor.Blue(), m_isDragging ? 220 : (m_isScrollbarHovered ? 180 : 128))));
            gc->SetPen(*wxTRANSPARENT_PEN);
            gc->DrawRectangle(scrollBarRect.x * 2, scrollBarRect.y * 2, scrollBarRect.width * 2, scrollBarRect.height * 2);
        }

        delete gc;
    }

    // Rescale bitmap for better quality
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
  /*
  * Better quality but laggy
  * roundedRectRegion = Utils::GetRoundedRegion(dc, GetClientSize() / 2, 10, 8);
  * dc.SetDeviceClippingRegion(roundedRectRegion);
  */
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

void RoundedScrollPanel::SetFocus()
{
}

void RoundedScrollPanel::OnSetFocus(wxFocusEvent& event) {
    // Intentionally empty to avoid gaining focus
}

void RoundedScrollPanel::OnKillFocus(wxFocusEvent& event) {
    // Intentionally empty to avoid focus-related issues
}

void RoundedScrollPanel::OnLeftDown(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();
    if (scrollBarRect.Contains(pos)) {
        m_isDragging = true;
        m_lastMouseY = pos.y;
        CaptureMouse();
        Refresh();
    }
}

void RoundedScrollPanel::OnMouseLeave(wxMouseEvent& event)
{
    bool shouldRefresh = false;
    wxPoint pos = event.GetPosition();

    if (m_isScrollbarHovered) {
        m_isScrollbarHovered = false;
        shouldRefresh = true;
    }

    if (shouldRefresh) Refresh();
}

void RoundedScrollPanel::OnMouseMove(wxMouseEvent& event) {
    if (m_isDragging && event.Dragging() && event.LeftIsDown()) {
        wxPoint pos = event.GetPosition();
        int diff = pos.y - m_lastMouseY;
        // Scale the difference based on the content height vs visible height ratio
        int scrollDiff = diff * m_totalContentHeight / GetClientSize().y;
        m_scrollPosition = std::max(0, std::min(m_scrollPosition + scrollDiff, m_totalContentHeight - GetClientSize().y));
        m_lastMouseY = pos.y;
        RecalculateLayout();
    }

    wxPoint pos = event.GetPosition();

    bool shouldRefresh = false;

    bool isHoveringScrollbar = scrollBarRect.Contains(pos);
    if (isHoveringScrollbar != m_isScrollbarHovered) {
        m_isScrollbarHovered = isHoveringScrollbar;
        shouldRefresh = true;
    }

    if (shouldRefresh) Refresh();
}

BEGIN_EVENT_TABLE(RoundedScrollPanel, wxPanel)
    EVT_SET_FOCUS(RoundedScrollPanel::OnSetFocus)
    EVT_KILL_FOCUS(RoundedScrollPanel::OnKillFocus)
    EVT_MOUSEWHEEL(RoundedScrollPanel::OnScroll)
    EVT_SIZE(RoundedScrollPanel::OnSize)
    EVT_PAINT(RoundedScrollPanel::OnPaint)
    EVT_LEFT_UP(RoundedScrollPanel::OnLeftUp)
    EVT_LEFT_DOWN(RoundedScrollPanel::OnLeftDown)
    EVT_LEAVE_WINDOW(RoundedScrollPanel::OnMouseLeave)
    EVT_MOTION(RoundedScrollPanel::OnMouseMove)
    EVT_ERASE_BACKGROUND(RoundedScrollPanel::OnEraseBackground)
END_EVENT_TABLE()