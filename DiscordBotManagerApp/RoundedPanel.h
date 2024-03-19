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
    /// <param name="offsetXT">Offset from the left.</param>
    /// <param name="offsetYT">Offset from the top.</param>
    /// <param name="offsetXB">Offset from the right.</param>
    /// <param name="offsetYB">Offset from the bottom.</param>
    RoundedPanel(wxWindow* parent, wxWindowID id = wxID_ANY, unsigned int offsetXT = 0, 
        unsigned int offsetYT = 0, unsigned int offsetXB = 0, unsigned int offsetYB = 0);

    /// <summary>
    /// Resizes the window in relation to window size.
    /// </summary>
    /// <param name="windowSize">Current window size.</param>
    /// <param name="defaultWindowSize">Size of the window that it is created with.</param>
    virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

    virtual bool SetBackgroundColour(const wxColour& colour);
    virtual bool SetForegroundColour(const wxColour& colour);
    virtual void SetRect(wxPoint pos, wxSize size);

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

    /// <summary>
    /// Function that is run whenever mouse button is pressed whilst over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnLeftDown(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever focus is set to the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnSetFocus(wxFocusEvent& event);
    
    wxColour bg;
    wxColour fg;
    unsigned int offsetXT; 
    unsigned int offsetYT; 
    unsigned int offsetXB; 
    unsigned int offsetYB;

    wxSize defaultSize;
    wxPoint defaultPos;

    DECLARE_EVENT_TABLE();
};

