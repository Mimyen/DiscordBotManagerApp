#include "ToggleButton.h"

ToggleButton::ToggleButton(wxPanel* parent, wxWindowID id, wxPoint pos, wxSize size, ButtonCallback callback, wxColour bg, wxColour active, wxColour inactive)
    : m_isToggled(false), wxPanel(parent, id , pos, size), m_hovered(false), m_clicked(false), m_hold(false), m_callback(callback)
{
    // Bind events
    Bind(wxEVT_PAINT, &ToggleButton::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &ToggleButton::OnMouseLeftUp, this);
    Bind(wxEVT_LEFT_DOWN, &ToggleButton::OnMouseLeftDown, this);
    Bind(wxEVT_ENTER_WINDOW, &ToggleButton::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &ToggleButton::OnMouseLeave, this);
    Bind(wxEVT_BUTTON, &ToggleButton::OnButtonClick, this);

    // Set background style that works with buffering
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Set variables
    this->bg = bg;
    this->active = active;
    this->inactive = inactive;
    this->defaultPos = pos;
    this->defaultSize = size;
}

void ToggleButton::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size for the element
    int buttonWidth = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int buttonHeight = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int buttonX = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int buttonY = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the button
    SetSize(buttonX, buttonY, buttonWidth, buttonHeight);
}

bool ToggleButton::GetState() const
{
    return m_isToggled;
}

void ToggleButton::SetState(const bool& state)
{
    if (m_isToggled == state) return;
    m_isToggled = state;
    Refresh();
}

void ToggleButton::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void ToggleButton::Render(wxDC& dc)
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

        // Draw rounded rectangle
        gc->SetBrush(wxBrush(m_isToggled ? active : inactive));
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, size.y);

        gc->SetBrush(wxBrush(bg));
        gc->DrawRoundedRectangle(
            m_isToggled ? size.x * 2 - (size.y * 2 - size.y / 6) : size.y / 6, 
            size.y / 6, 
            size.y * 2 - size.y / 6 * 2, 
            size.y * 2 - size.y / 6 * 2, 
            size.y - size.y / 6
        );

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

void ToggleButton::OnMouseEnter(wxMouseEvent& event)
{
    m_hovered = true;
    event.Skip();
}

void ToggleButton::OnMouseLeave(wxMouseEvent& event)
{
    if (m_hovered) {
        if (!m_hold) ;
        else ;
        m_hovered = false;
        m_clicked = false;
        m_hold = false;
        event.Skip();
    }
}

void ToggleButton::OnMouseLeftUp(wxMouseEvent& event)
{
    if (m_clicked) {
        m_clicked = false;
        m_hold = false;
        m_isToggled = !m_isToggled;
        wxCommandEvent evt(wxEVT_BUTTON, GetId());
        GetEventHandler()->ProcessEvent(evt);
        Refresh();
    }

    event.Skip();
}

void ToggleButton::OnMouseLeftDown(wxMouseEvent& event)
{
    m_clicked = true;
    m_hold = true;
    event.Skip();
}

void ToggleButton::OnButtonClick(wxCommandEvent& event)
{
    if (m_callback) m_callback(m_isToggled);
}
