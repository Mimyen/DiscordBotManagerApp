#include "ScrollControl.h"

void ScrollControl::SetPosition(const wxPoint& pos)
{
	m_position = pos;
}

void ScrollControl::SetSize(const wxSize& size)
{
	m_size = size;
}

void ScrollControl::SetHover(const bool& isHovered)
{
	m_isHovered = isHovered;
}

void ScrollControl::SetHoverColour(const wxColour& colour)
{
	hoverColour = colour;
}

void ScrollControl::SetDefaultColour(const wxColour& colour)
{
	defaultColour = colour;
}

wxPoint ScrollControl::GetPosition() const
{
	return m_position;
}

wxSize ScrollControl::GetSize() const
{
	return m_size;
}

bool ScrollControl::GetHover() const
{
	return m_isHovered;
}

bool ScrollControl::HitTest(const wxPoint& pt) const
{
	// Adjust pt by the scroll position for accurate hit testing
	wxPoint adjustedPt = pt;
	adjustedPt.y += m_parent->GetScrollPos(wxVERTICAL); // Assuming vertical scrolling
	return wxRect(m_position, m_size).Contains(adjustedPt);
}
