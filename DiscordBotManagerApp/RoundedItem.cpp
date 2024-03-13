#include "RoundedItem.h"

RoundedItem::RoundedItem(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, bool showIcon, wxString iconPath)
    : bg(wxColour(18, 18, 18)), m_showIcon(showIcon), m_isSelected(false), m_isHovered(false), m_isPressed(false),
    wxPanel(parent, id, pos, size), m_isShown(false), hover(wxColour(114, 114, 114))
{
    if (m_showIcon) {
        if (!icon.LoadFile(iconPath, wxBITMAP_TYPE_PNG)) {
            wxLogError("Couldn't load icon.");
        }
    }


}

bool RoundedItem::SetBackgroundColour(const wxColour& colour)
{
    try {
        bg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool RoundedItem::SetForegroundColour(const wxColour& colour)
{
    try {
        fg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool RoundedItem::SetHoverColour(const wxColour& colour)
{
    try {
        hover = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

void RoundedItem::SetSelected(const bool& state)
{
    this->m_isSelected = state;
}
