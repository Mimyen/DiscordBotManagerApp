#pragma once

#include "ColorPickerPopup.h"

class ColorPicker : public wxPanel
{
public:
	using Callback = std::function<void(unsigned int r, unsigned int g, unsigned int b)>;

	ColorPicker(wxWindow* parent, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize,
		Callback onColorChange = [](unsigned int r, unsigned int g, unsigned int b) {});

	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

	virtual bool SetBackgroundColour(const wxColour& colour);
	virtual bool SetOutlineActiveColour(const wxColour& colour);
	virtual bool SetOutlineInactiveColour(const wxColour& colour);
	virtual std::vector<int> GetRGB() const;

	ColorPickerPopup* m_popup;
private:
    /// <summary>
    /// Inner function that draws the element.
    /// </summary>
    /// <param name="dc">Drawing component from wxWidgets.</param>
    virtual void Render(wxDC& dc);

    /// <summary>
    /// Repaints the window.
    /// </summary>
    /// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
    virtual void OnPaint(wxPaintEvent& event);

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
	/// Function that is run whenever mouse enters the element.
	/// </summary>
	/// <param name="event">Event passed to the function.</param>
	virtual void OnMouseEnter(wxMouseEvent& event);

	/// <summary>
	/// Function that is run whenever mouse leaves the element.
	/// </summary>
	/// <param name="event">Event passed to the function.</param>
	virtual void OnMouseLeave(wxMouseEvent& event);

	unsigned int m_r;
	unsigned int m_g;
	unsigned int m_b;
	wxColour bg;
	wxColour outlineActive;
	wxColour outlineInactive;
	wxSize defaultSize;
	wxPoint defaultPos;
	bool m_hovered;
	bool m_clicked;
	bool m_hold;
	Callback m_callback;
	DECLARE_EVENT_TABLE()
};

