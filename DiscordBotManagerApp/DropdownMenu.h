#pragma once

#include "Utils.h"
#include "MenuPopup.h"

/// <summary>
/// Class that creates dropdown menus.
/// </summary>
class DropdownMenu : public wxPanel
{
public:
	using FunctionCallback = std::function<void(wxString option)>;
	/// <summary>
	/// Contructor for DropdownMenu class.
	/// </summary>
	/// <param name="parent">Pointer to cointainer that Image class will be in.</param>
	/// <param name="id">Id of the object, useable for making calls.</param>
	/// <param name="pos">Position where Image will be drawn.</param>
	/// <param name="size">Size of the Image.</param>
	DropdownMenu(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, FunctionCallback callback = [](wxString option = "") {}, wxString defaultLabel = "Select Option", wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT));

	/// <summary>
	/// Adds item to menu.
	/// </summary>
	/// <param name="item">wxString representing the chosen item from the menu</param>
	/// <returns></returns>
	virtual void AddItem(const wxString& item);

	/// <summary>
	/// Sets items.
	/// </summary>
	/// <param name="item">wxString representing the chosen item from the menu</param>
	/// <returns></returns>
	virtual void SetItems(const std::vector<wxString>& items);

	virtual std::vector<wxString> GetItems() const;

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

	FunctionCallback m_callback;
	std::vector<wxString> m_items;
	bool m_isMenuVisible;

	wxSize defaultSize;
	wxPoint defaultPos;
	wxString selectedOption;
	wxString m_defaultLabel;
	unsigned int defaultFontSize;
};

