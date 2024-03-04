#include "RoundedPanel.h"

RoundedPanel::RoundedPanel(wxWindow* parent, wxWindowID id, wxColour fg, wxColour bg, unsigned int offsetXT, unsigned int offsetYT, unsigned int offsetXB, unsigned int offsetYB) : wxPanel(parent, id)
{
    // Bind resizing event
    Bind(wxEVT_SIZE, &RoundedPanel::OnSize, this);

    // Set variables
    this->bg = bg;
    this->fg = fg;
    this->offsetXT = offsetXT;
    this->offsetYT = offsetYT;
    this->offsetXB = offsetXB;
    this->offsetYB = offsetYB;
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
    dc.DrawRoundedRectangle(offsetXT, offsetYT, size.x - offsetXB, size.y - offsetYB, radius);
}

void RoundedPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    event.Skip();
}

wxBEGIN_EVENT_TABLE(RoundedPanel, wxPanel)
EVT_PAINT(RoundedPanel::OnPaint)
wxEND_EVENT_TABLE()