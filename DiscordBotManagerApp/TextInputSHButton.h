#pragma once

#include "libs.h"
#include "TextInput.h"


/// <summary>
/// This class is inner class of TextInputPanel component. 
/// It's responsible for printing button that toggles encryption.
/// </summary>
class TextInputSHButton : public wxPanel
{
public:
	/// <summary>
	/// Constructor for RoundedButton class.
	/// </summary>
	/// <param name="parent">Pointer to cointainer that component will be in.</param>
	/// <param name="id">Id of the object, useable for making calls.</param>
	/// <param name="input">Pointer to TextInput element related to button.</param>
	/// <param name="bg">Color of the background.</param>
	TextInputSHButton(wxWindow* parent, wxWindowID id = wxID_ANY, TextInput* input = nullptr);

	virtual bool SetBackgroundColour(const wxColour& colour);
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
	virtual void OnButtonClick();

	bool isShown;
	bool isHovered;
	bool isPressed;

	wxImage show;
	wxImage hide;

	wxImage lastShow;
	wxImage lastHide;

	wxColour bg;

	TextInput* m_input;
};

