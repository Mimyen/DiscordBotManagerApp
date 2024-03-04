#pragma once

#include "libs.h"


/// <summary>
/// This class draws simple rectangle filled with colour.
/// </summary>
class RectangleObj : public wxPanel
{
public:
    /// <summary>
    /// Constructor for RectangleObj class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that component will be in.</param>
    /// <param name="id">Id of the object, useable for making calls.</param>
    /// <param name="pos">Position where component will be drawn.</param>
    /// <param name="size">Size of the component.</param>
    /// <param name="bg">Color of the background.</param>
    /// <param name="fg">Color of the text.</param>
    RectangleObj(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, wxColour fg = wxColour(41, 41, 41), wxColour bg = wxColour(18, 18, 18));
    
    /// <summary>
    /// Resizes the window in relation to window size.
    /// </summary>
    /// <param name="windowSize">Current window size.</param>
    /// <param name="defaultWindowSize">Size of the window that it is created with.</param>
    virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

protected:
    /// <summary>
    /// Repaints the window.
    /// </summary>
    /// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
    virtual void OnPaint(wxPaintEvent& event);
    
    /// <summary>
    /// Inner function that draws the element.
    /// </summary>
    /// <param name="dc">Drawing component from wxWidgets.</param>
    virtual void Render(wxDC& dc);

    wxSize defaultSize;
    wxPoint defaultPos;
    wxColour bg;
    wxColour fg;
};

