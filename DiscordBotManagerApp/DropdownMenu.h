#pragma once

#include "Utils.h"
#include "MenuPopup.h"

class DropdownMenu : public wxPanel
{
public:
	DropdownMenu(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize);

	/// <summary>
	/// Adds item to menu.
	/// </summary>
	/// <param name="item">wxString representing the chosen item from the menu</param>
	/// <returns></returns>
	virtual void AddItem(const wxString& item);

	/// <summary>
	/// Select item from menu.
	/// </summary>
	/// <param name="item">wxString representing the chosen item from the menu</param>
	/// <returns></returns>
	virtual void Select(const wxString& item);

	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

	bool isOpen;

protected:
	/// <summary>
	/// Repaints the window.
	/// </summary>
	/// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
	/// <returns></returns>
	virtual void Render(wxDC& dc);

	/// <summary>
	/// Inner function that draws the element.
	/// </summary>
	/// <param name="dc">Drawing component from wxWidgets.</param>
	virtual void OnPaint(wxPaintEvent& event);

	/// <summary>
	/// Function that is run whenever mouse button is pressed whilst over the element.
	/// </summary>
	/// <param name="event">Event passed to the function.</param>
	virtual void OnMouseLeftDown(wxMouseEvent& event);

	std::vector<wxString> m_items;
	bool m_isMenuVisible;

	wxSize defaultSize;
	wxPoint defaultPos;
	wxString selectedOption;
};

