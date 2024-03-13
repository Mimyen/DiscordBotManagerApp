#include "RoundedPanel.h"

RoundedPanel::RoundedPanel(wxWindow* parent, wxWindowID id, unsigned int offsetXT, unsigned int offsetYT, unsigned int offsetXB, unsigned int offsetYB) : wxPanel(parent, id)
{
    // Bind resizing event
    Bind(wxEVT_SIZE, &RoundedPanel::OnSize, this);

    // Set variables
    this->bg = wxColour(0, 0, 0);
    this->fg = wxColour(18, 18, 18);
    this->offsetXT = offsetXT;
    this->offsetYT = offsetYT;
    this->offsetXB = offsetXB;
    this->offsetYB = offsetYB;
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

void RoundedPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    Render(dc);
}

void RoundedPanel::Render(wxDC& dc)
{
    // Get size of the panel
    wxSize size = GetClientSize();
    int radius = 10;

    // Set background color
    dc.SetBrush(wxBrush(fg));
    dc.SetPen(*wxTRANSPARENT_PEN);

    // Draw rounded rectangle
    dc.DrawRoundedRectangle(offsetXT, offsetYT, size.x - offsetXB, size.y - offsetYB - offsetYT, radius);
}

void RoundedPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    event.Skip();
}

wxBEGIN_EVENT_TABLE(RoundedPanel, wxPanel)
EVT_PAINT(RoundedPanel::OnPaint)
wxEND_EVENT_TABLE()