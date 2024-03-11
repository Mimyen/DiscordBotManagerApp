#pragma once

#include "Utils.h"
#include "ScrollButton.h"

class ScrollPanel : public wxPanel {
public:
    using FunctionCallback = std::function<void()>;
    ScrollPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, FunctionCallback callback = []() {});

    template<typename T, typename... Args>
    void AddScrollControl(Args&&... args) {
        m_scrollControls.emplace_back(std::make_unique<T>(this, std::forward<Args>(args)...));
        RecalculateLayout();
    }

    void RecalculateLayout(); // Used after adding controls or resizing

protected:
    void OnScroll(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnSetFocus(wxFocusEvent& event);
    void OnKillFocus(wxFocusEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);
    void Render(wxDC& dc);
    void SetFocus();

private:
    std::vector<std::unique_ptr<ScrollControl>> m_scrollControls;
    int m_scrollPosition; // Current scroll position
    int m_totalContentHeight; // Total content height
    int m_lastMouseY;
    wxRect scrollBarRect;
    bool m_isDragging;
    bool m_isScrollbarHovered;
    FunctionCallback m_callback;

    DECLARE_EVENT_TABLE()
};
