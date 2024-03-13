#pragma once

#include "Utils.h"

class RoundedItem : public wxPanel
{
public:
	RoundedItem(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, 
		wxSize size = wxDefaultSize, bool showIcon = false, wxString iconPath = "");

	virtual bool SetBackgroundColour(const wxColour& colour);
	virtual bool SetForegroundColour(const wxColour& colour);
	virtual bool SetHoverColour(const wxColour& colour);
	virtual void SetSelected(const bool& state);
protected:
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

	wxSize defaultSize;
	wxPoint defaultPos;
};

