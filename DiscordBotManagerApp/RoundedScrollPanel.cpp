#include "RoundedScrollPanel.h"

RoundedScrollPanel::RoundedScrollPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size)
    : m_scrollPosition(0), m_totalContentHeight(0), m_isDragging(false), m_lastMouseY(0), 
    m_isScrollbarHovered(false), bg(wxColour(0, 0, 0)), fg(wxColour(0, 0, 0)),
    defaultPos(pos), defaultSize(size)
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

    // Use the full width of the RoundedScrollPanel for each control
    int controlWidth = GetClientSize().x;
    int yPos = controlWidth / 8; // Start from the very top

    for (auto& control : m_scrollControls) {
        // Update each control's position and size to fill the panel horizontally
        control->SetPosition(wxPoint(controlWidth / 8, yPos - m_scrollPosition));
        control->SetSize(wxSize(std::round((double)controlWidth * 3.0 / 4.0), std::round((double)controlWidth * 3.0 / 4.0)));

        // Move yPos for the next control, placing it directly below the previous one without a gap
        yPos += control->GetSize().y + controlWidth / 8;
    }

    // Adjust the total content height based on the final yPos
    m_totalContentHeight = yPos;

    Refresh(); // Redraw to apply layout changes
}

void RoundedScrollPanel::UnselectAll()
{
    for (auto& control : m_scrollControls) {
        if (control->GetSelected()) {
            control->SetSelected(false);
            control->Refresh();
        }
    }
}

void RoundedScrollPanel::SelectAll()
{
    for (auto& control : m_scrollControls) {
        if (!control->GetSelected()) {
            control->SetSelected(true);
            control->Refresh();
        }
    }
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
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp(size * 2);
    wxMemoryDC memDC;
    memDC.SelectObject(bmp);

    // Set the background color
    memDC.SetBackground(wxBrush(bg));
    memDC.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        // Draw the rounded rectangle on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

        gc->SetBrush(wxBrush(fg));
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, 24);

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
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

void RoundedScrollPanel::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int objectX = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int objectY = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int objectWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int objectHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the object
    SetSize(objectWidth, objectHeight, objectX, objectY);

    for (auto& control : m_scrollControls) {
        control->UpdateFontSize((double)windowSize.y / (double)defaultWindowSize.y);
    }

    RecalculateLayout();

    Refresh();
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