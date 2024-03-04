#pragma once
#include "libs.h"

/// <summary>
/// This class creates a panel that has background that is rounded rectangle.
/// </summary>
class RoundedPanel : public wxPanel
{
public:
	/// <summary>
	/// Constructor for RoundedPanel class.
	/// </summary>
	/// <param name="parent">Pointer to cointainer that component will be in.</param>
	/// <param name="id">Id of the object, useable for making calls.</param>
	/// <param name="fg">Color of the text.</param>
    /// <param name="offsetXT">Offset from the left.</param>
    /// <param name="offsetYT">Offset from the top.</param>
    /// <param name="offsetXB">Offset from the right.</param>
    /// <param name="offsetYB">Offset from the bottom.</param>
    RoundedPanel(wxWindow* parent, wxWindowID id = wxID_ANY, wxColour fg = wxColour(18, 18, 18), wxColour bg = wxColour(0, 0, 0), 
        unsigned int offsetXT = 0, unsigned int offsetYT = 0, unsigned int offsetXB = 0, unsigned int offsetYB = 0);

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

    /// <summary>
    /// Function that is called whenever window changes it's size.
    /// </summary>
    /// <param name="event">Event that is called.</param>
    virtual void OnSize(wxSizeEvent& event);
    
    wxColour bg;
    wxColour fg;
    unsigned int offsetXT; 
    unsigned int offsetYT; 
    unsigned int offsetXB; 
    unsigned int offsetYB;

    DECLARE_EVENT_TABLE();
};

