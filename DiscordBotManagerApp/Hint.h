#pragma once

#include "Utils.h"

class Hint : public wxPopupTransientWindow
{
public:
	Hint(wxWindow* parent, wxString label = "");

private:
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

	wxString m_label;

	DECLARE_EVENT_TABLE()
};

