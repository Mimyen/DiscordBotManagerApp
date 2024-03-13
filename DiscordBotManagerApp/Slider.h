#pragma once

#include "Utils.h"

class Slider : public wxPanel
{
public:
	using FunctionCallback = std::function<void(double value)>;

	Slider(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, FunctionCallback callback = [](double value = 0.0) {});

	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

	virtual bool SetBackgroundColour(const wxColour& colour);
	virtual bool SetBarColour(const wxColour& colour);
	virtual bool SetHoverColour(const wxColour& colour);
	virtual bool SetForegroundColour(const wxColour& colour);
	virtual void SetValue(const double& value);

	virtual double GetValue() const;
protected:
	virtual void Render(wxDC& dc);
	virtual void OnPaint(wxPaintEvent& event);
	virtual void OnMouseEnter(wxMouseEvent& event);
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
	/// Function that is run whenever mouse is being moved over the element.
	/// </summary>
	/// <param name="event">Event passed to the function.</param>
	void OnMouseMove(wxMouseEvent& event);


	wxColour bg;
	wxColour bar;
	wxColour hover;
	wxColour fg;
	double m_value;
	FunctionCallback m_callback;
	wxPoint defaultPos;
	wxSize defaultSize;
	bool m_isHovered;
	bool m_isDragging;

	DECLARE_EVENT_TABLE()
};

