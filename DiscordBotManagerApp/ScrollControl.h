#pragma once

#include "Utils.h"

/// <summary>
/// Inner ScrollPanel class.
/// Virtual class responsible for making elements of the ScrollPanel.
/// </summary>
class ScrollControl
{
public:
    /// <summary>
    /// Contructor for ScrollButton class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that Image class will be in.</param>
    /// <param name="pos">Position where Image will be drawn.</param>
    /// <param name="size">Size of the popup.</param>
    ScrollControl(wxWindow* parent, wxPoint pos, wxSize size)
        : m_parent(parent), m_position(pos), m_size(size), 
        defaultColour(wxColour(60, 60, 60)), hoverColour(wxColour(90, 90, 90)), m_isHovered(false) {}

    /// <summary>
    /// Destructor for ScrollButton class.
    /// </summary>
    virtual ~ScrollControl() {}

    /// <summary>
    /// Repaints the button.
    /// </summary>
    /// <param name="gc">wxGraphicsContext provided by the parent.</param>
    virtual void Draw(wxGraphicsContext* gc) = 0;

    /// <summary>
    /// Function that is run whenever button is clicked.
    /// (Though you need to add event functionality yourself)
    /// </summary>
    virtual void OnClick() = 0;

    /// <summary>
    /// Sets position of the element.
    /// </summary>
    /// <param name="pos">wxPoint containing desired position.</param>
    void SetPosition(const wxPoint& pos);

    /// <summary>
    /// Sets size of the element.
    /// </summary>
    /// <param name="size">wxSize containing desired size.</param>
    void SetSize(const wxSize& size);

    /// <summary>
    /// Changes whether element is hovered.
    /// </summary>
    /// <param name="isHovered">boolean value containing information whether it's hovered or not.</param>
    void SetHover(const bool& isHovered);

    /// <summary>
    /// Sets on hover colour of the element.
    /// </summary>
    /// <param name="colour">wxColour containing desired colour</param>
    void SetHoverColour(const wxColour& colour);

    /// <summary>
    /// Sets on hover colour of the element.
    /// </summary>
    /// <param name="colour">wxColour containing desired colour</param>
    void SetDefaultColour(const wxColour& colour);

    /// <summary>
    /// Returns current position of the element.
    /// </summary>
    /// <returns>wxPoint containing position</returns>
    wxPoint GetPosition() const;

    /// <summary>
    /// Returns current size of the element.
    /// </summary>
    /// <returns>wxSize containing size</returns>
    wxSize GetSize() const;

    /// <summary>
    /// Returns current hover state.
    /// </summary>
    /// <returns>boolean value (true - hovered)</returns>
    bool GetHover() const;

    /// <summary>
    /// Checks if button was clicked.
    /// </summary>
    /// <returns>boolean value (true - clicked)</returns>
    bool HitTest(const wxPoint& pt) const;

protected:
    wxWindow* m_parent;
    wxPoint m_position;
    wxSize m_size;
    bool m_isHovered;

    wxColour defaultColour;
    wxColour hoverColour;
};

