#include "RoundedPanel.h"

RoundedPanel::RoundedPanel(wxWindow* parent, wxWindowID id, unsigned int offsetXT, unsigned int offsetYT, unsigned int offsetXB, unsigned int offsetYB) : wxPanel(parent, id)
{

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Set variables
    this->bg = wxColour(0, 0, 0);
    this->fg = wxColour(18, 18, 18);
    this->offsetXT = offsetXT;
    this->offsetYT = offsetYT;
    this->offsetXB = offsetXB;
    this->offsetYB = offsetYB;
}

void RoundedPanel::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int objectX = defaultSize.x * windowSize.x / defaultWindowSize.x; 
    int objectY = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int objectWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int objectHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the object
    SetSize(objectWidth, objectHeight, objectX, objectY);
}

bool RoundedPanel::SetBackgroundColour(const wxColour& colour)
{
    try {
        bg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool RoundedPanel::SetForegroundColour(const wxColour& colour)
{
    try {
        fg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

void RoundedPanel::SetRect(wxPoint pos, wxSize size)
{
    SetSize(size);
    defaultSize = size;

    SetPosition(pos);
    defaultPos = pos;
}

void RoundedPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void RoundedPanel::Render(wxDC& dc)
{
    dc.Clear();

    // Get size of the panel
    wxSize size = GetClientSize();

    // Set background color
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBackground(wxBrush(bg));

    // Draw rounded rectangle
    dc.SetBrush(wxBrush(bg));
    dc.DrawRectangle(0, 0, size.x, size.y);
    dc.SetBrush(wxBrush(fg));
    dc.DrawRoundedRectangle(offsetXT, offsetYT, size.x - offsetXB, size.y - offsetYB - offsetYT, 12);
}

void RoundedPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    event.Skip();
}

void RoundedPanel::OnLeftDown(wxMouseEvent& event)
{

}

void RoundedPanel::OnSetFocus(wxFocusEvent& event)
{
}

void RoundedPanel::OnNavigationKeyPress(wxNavigationKeyEvent& event)
{
    if (event.IsFromTab()) event.Skip();
}

wxBEGIN_EVENT_TABLE(RoundedPanel, wxPanel)
    EVT_PAINT(RoundedPanel::OnPaint)
    EVT_LEFT_DOWN(RoundedPanel::OnLeftDown)
    EVT_SET_FOCUS(RoundedPanel::OnSetFocus)
    EVT_NAVIGATION_KEY(RoundedPanel::OnNavigationKeyPress)
    EVT_SIZE(RoundedPanel::OnSize)
wxEND_EVENT_TABLE()