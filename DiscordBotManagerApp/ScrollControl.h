#pragma once

#include "Utils.h"

class ScrollControl
{
public:
    ScrollControl(wxWindow* parent, wxPoint pos, wxSize size)
        : m_parent(parent), m_position(pos), m_size(size), 
        defaultColour(wxColour(114, 114, 114)), hoverColour(wxColour(60, 60, 60)), m_isHovered(false) {}

    virtual ~ScrollControl() {}

    virtual void Draw(wxGraphicsContext* gc) = 0; // Implement in derived classes
    virtual void OnClick() = 0; // Implement click behavior in derived classes

    // New methods for setting position and size
    void SetPosition(const wxPoint& pos) { m_position = pos; }
    void SetSize(const wxSize& size) { m_size = size; }
    void SetHover(const bool& isHovered) { m_isHovered = isHovered; }
    void SetHoverColour(const wxColour& colour) { hoverColour = colour; }
    void SetDefaultColour(const wxColour& colour) { defaultColour = colour; }

    wxPoint GetPosition() const { return m_position; }
    wxSize GetSize() const { return m_size; }
    bool GetHover() const { return m_isHovered; }

    bool HitTest(const wxPoint& pt) const {
        // Adjust pt by the scroll position for accurate hit testing
        wxPoint adjustedPt = pt;
        adjustedPt.y += m_parent->GetScrollPos(wxVERTICAL); // Assuming vertical scrolling
        return wxRect(m_position, m_size).Contains(adjustedPt);
    }

protected:
    wxWindow* m_parent;
    wxPoint m_position;
    wxSize m_size;
    bool m_isHovered;

    wxColour defaultColour;
    wxColour hoverColour;
};

