#pragma once
#include "libs.h"

/// <summary>
/// This class draws button that we can toggle between two states.
/// </summary>
class ToggleButton : public wxPanel
{
public:
    /// <summary>
    /// Callback to the function that will be run whenever button is clicked.
    /// </summary>
    using ButtonCallback = std::function<void(bool flag)>;

    /// <summary>
    /// Constructor for RoundedButton class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that component will be in.</param>
    /// <param name="id">Id of the object, useable for making calls.</param>
    /// <param name="pos">Position where component will be drawn.</param>
    /// <param name="size">Size of the component.</param>
    /// <param name="callback">Function that will be run when button is clicked.</param>>
    /// <param name="bg">Color of the background.</param>
    /// <param name="active">Color of the active toggle.</param>
    /// <param name="inactive">Color of the inactive toggle.</param>
    ToggleButton(wxPanel* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, ButtonCallback callback = [](bool flag = true) {},
        wxColour bg = wxColour(18, 18, 18), wxColour active = wxColour(26, 188, 156), wxColour inactive = wxColour(114, 114, 114));
    
    /// <summary>
    /// Resizes the window in relation to window size.
    /// </summary>
    /// <param name="windowSize">Current window size.</param>
    /// <param name="defaultWindowSize">Size of the window that it is created with.</param>
    virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);
    
    /// <summary>
    /// Getter function for State.
    /// </summary>
    /// <returns>State of the button.</returns>
    virtual bool GetState() const;

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
    /// Function that is run whenever mouse enters the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseEnter(wxMouseEvent& event);
    
    /// <summary>
    /// Function that is run whenever mouse leaves the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseLeave(wxMouseEvent& event);
    
    /// <summary>
    /// Function that is run whenever mouse button is lift whilst over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseLeftUp(wxMouseEvent& event);
    
    /// <summary>
    /// Function that is run whenever mouse button is pressed whilst over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseLeftDown(wxMouseEvent& event);
    
    /// <summary>
    /// Function that is run whenever button is clicked (callback is being run).
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnButtonClick(wxCommandEvent& event);

    ButtonCallback m_callback;

    wxColour bg;
    wxColour active;
    wxColour inactive;
    wxPoint defaultPos;
    wxSize defaultSize;
    bool m_isToggled;
    bool m_hovered;
    bool m_clicked;
    bool m_hold;
};

