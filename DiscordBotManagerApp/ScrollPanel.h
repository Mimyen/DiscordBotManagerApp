#pragma once

#include "Utils.h"
#include "ScrollButton.h"


/// <summary>
/// Simple Panel with scroll functionalities.
/// </summary>
class ScrollPanel : public wxPanel {
public:
    using FunctionCallback = std::function<void()>;

    /// <summary>
    /// Contructor for ScrollPanel class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that Image class will be in.</param>
    /// <param name="pos">Position where Image will be drawn.</param>
    /// <param name="size">Size of the popup.</param>
    /// <param name="callback">Callback to a function</param>
    ScrollPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, FunctionCallback callback = []() {});

    /// <summary>
    /// Adds control to the panel. Need to specify class and arguments of the control.
    /// </summary>
    /// <param name="args">arguments needed to create object of desired class.</param>
    template<typename T, typename... Args>
    void AddScrollControl(Args&&... args) {
        m_scrollControls.emplace_back(std::make_unique<T>(this, std::forward<Args>(args)...));
        RecalculateLayout();
    }
    
    /// <summary>
    /// Recalculates layout of the panel.
    /// </summary>
    void RecalculateLayout();

protected:
    /// <summary>
    /// Function that is run whenever user wants to scroll the panel.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnScroll(wxMouseEvent& event);

    /// <summary>
    /// Function that is called whenever window changes it's size.
    /// </summary>
    /// <param name="event">Event that is called.</param>
    void OnSize(wxSizeEvent& event);

    /// <summary>
    /// Repaints the window.
    /// </summary>
    /// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
    void OnPaint(wxPaintEvent& event);

    /// <summary>
    /// Function that is run whenever mouse button is lift whilst over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnLeftUp(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever background is being erased.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnEraseBackground(wxEraseEvent& event);

    /// <summary>
    /// Function that is run whenever focus is being set to the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnSetFocus(wxFocusEvent& event);

    /// <summary>
    /// Function that is run whenever elements loses the focus.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnKillFocus(wxFocusEvent& event);

    /// <summary>
    /// Function that is run whenever mouse is being moved over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnMouseMove(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever mouse button is pressed whilst over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnLeftDown(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever mouse leaves the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    void OnMouseLeave(wxMouseEvent& event);

    /// <summary>
    /// Inner function that draws the element.
    /// </summary>
    /// <param name="dc">Drawing component from wxWidgets.</param>
    void Render(wxDC& dc);

    /// <summary>
    /// Sets focus to the element.
    /// </summary>
    void SetFocus();

private:
    std::vector<std::unique_ptr<ScrollControl>> m_scrollControls;
    int m_scrollPosition; // Current scroll position
    int m_totalContentHeight; // Total content height
    int m_lastMouseY;
    wxRect scrollBarRect;
    bool m_isDragging;
    bool m_isScrollbarHovered;
    bool m_rectInitialized;
    FunctionCallback m_callback;
    wxRegion roundedRectRegion;
    wxBitmap emptyBitmap;
    DECLARE_EVENT_TABLE()
};
