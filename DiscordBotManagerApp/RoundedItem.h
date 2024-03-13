#pragma once

#include "Utils.h"

class RoundedItem : public wxPanel
{
public:
	using ButtonCallback = std::function<void()>;

	RoundedItem(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, 
		wxSize size = wxDefaultSize, ButtonCallback callback = []() {}, bool showIcon = false, wxString iconPath = "");

	virtual bool SetBackgroundColour(const wxColour& colour);
	virtual bool SetForegroundColour(const wxColour& colour);
	virtual bool SetHoverColour(const wxColour& colour);
	virtual bool SetSelectedColour(const wxColour& colour);
	virtual void SetSelected(const bool& state);
	virtual bool GetSelected() const;
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

	bool m_isShown;
	bool m_isHovered;
	bool m_isPressed;
	bool m_isSelected;
	bool m_showIcon;

	wxImage icon;

	wxImage lastIcon;

	wxColour bg;
	wxColour fg;
	wxColour hover;
	wxColour selected;

	wxSize defaultSize;
	wxPoint defaultPos;

	ButtonCallback m_callback;

	DECLARE_EVENT_TABLE()
};

