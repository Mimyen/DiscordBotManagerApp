#pragma once

#include "Utils.h"
#include "MenuPopup.h"

class DropdownMenu : public wxPanel
{
public:
	DropdownMenu(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize);
	virtual void AddItem(const wxString& item);
	virtual void ShowMenu();
	virtual void HideMenu();	

	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

	bool isOpen;

protected:
	virtual void Render(wxDC& dc);
	virtual void OnPaint(wxPaintEvent& event);
	virtual void OnMouseLeftDown(wxMouseEvent& event);

	std::vector<wxString> m_items;
	bool m_isMenuVisible;

	wxSize defaultSize;
	wxPoint defaultPos;
	wxString selectedOption;
};

