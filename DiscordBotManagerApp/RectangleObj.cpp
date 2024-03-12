#include "RectangleObj.h"

RectangleObj::RectangleObj(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, wxColour fg, wxColour bg) 
    : wxPanel(parent, id , pos, size)
{
    // Bind repainting event
    Bind(wxEVT_PAINT, &RectangleObj::OnPaint, this);

    // Save default size and position
    defaultSize = size;
    defaultPos = pos;

    // Set colors for the element
    this->fg = fg;
    this->bg = bg;
}

void RectangleObj::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int objectX = defaultSize.x * windowSize.x / defaultWindowSize.x; 
    int objectY = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int objectWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int objectHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the object
    SetSize(objectWidth, objectHeight, objectX, objectY);

    Refresh();
}

void RectangleObj::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    Render(dc);
}

void RectangleObj::Render(wxDC& dc)
{
    // Get size of the panel
    wxSize size = GetClientSize();

    // Set background color
    dc.SetBrush(wxBrush(fg));
    dc.SetPen(*wxTRANSPARENT_PEN);

    // Draw rounded rectangle
    dc.DrawRectangle(0, 0, size.x, size.y);
}