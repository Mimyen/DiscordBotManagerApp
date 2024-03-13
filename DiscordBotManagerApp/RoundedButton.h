#pragma once
#include "libs.h"

/// <summary>
/// This class draws button width rounded corners (a capsule).
/// </summary>
class RoundedButton : public wxPanel
{
public: 
	/// <summary>
	/// Callback to the function that will be run whenever button is clicked.
	/// </summary>
	using ButtonCallback = std::function<void()>;

	/// <summary>
	/// Constructor for RoundedButton class.
	/// </summary>
	/// <param name="parent">Pointer to cointainer that component will be in.</param>
	/// <param name="id">Id of the object, useable for making calls.</param>
	/// <param name="label">Label displayed on the button.</param>
	/// <param name="pos">Position where component will be drawn.</param>
	/// <param name="size">Size of the component.</param>
	/// <param name="callback">Function that will be run when button is clicked.</param>
	/// <param name="master">Pointer to the window</param>
	/// <param name="drawOutline">Changes whether outline will be drawn or not.</param>
	/// <param name="outlineSize">Thickness of the outline.</param>
	RoundedButton(wxWindow* parent, const wxString& label, const wxPoint& position, const wxSize& size, 
		ButtonCallback callback, bool drawOutline = false, unsigned int outlineSize = 2);

	/// <summary>
	/// Setter function for the label.
	/// </summary>
	/// <param name="label">Label that will be displayed on the button.</param>
	virtual void SetLabel(const wxString& label);

	/// <summary>
	/// Setter function for the font.
	/// </summary>
	/// <param name="font">Font that will be set.</param>
	virtual void SetFont(wxFont font);

	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

	virtual bool SetBackgroundColour(const wxColour& colour);
	virtual bool SetForegroundColour(const wxColour& colour);
	virtual bool SetOutlineColour(const wxColour& colour);
	virtual bool SetPressedColour(const wxColour& colour);
	virtual bool SetColour(const wxColour& colour);

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

	/// <summary>
	/// Function that reduces the size of element.
	/// </summary>
	virtual void Reduce();

	/// <summary>
	/// Function that increases the size of element.
	/// </summary>
	virtual void Increase();

	ButtonCallback m_callback;

	wxString m_label;
	wxSize defaultSize;
	wxPoint defaultPos;
	wxFont font;
	bool m_hovered;
	bool m_clicked;
	bool m_hold;
	bool drawOutline;
	wxColour colour;
	wxColour clicked;
	wxColour bg;
	wxColour fg;
	wxColour outline;
	int radius;
	int fontDefaultSize;
	unsigned int outlineSize;
};

