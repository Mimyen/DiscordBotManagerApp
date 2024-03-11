#pragma once

#include "ScrollPanel.h"

class MenuPopup : public wxPopupTransientWindow
{
public:
    using ButtonCallback = std::function<void(wxString item)>;

    MenuPopup(wxWindow* parent, const wxSize& size, bool* open = nullptr, std::vector<wxString> options = std::vector<wxString>(), 
        wxString* selectedOption = nullptr, ButtonCallback callback = [](wxString item = "") {});

    // Override the OnPaint method to customize the appearance of the popup
    void OnPaint(wxPaintEvent& event);

    // Override the OnDismiss method to perform cleanup when the popup is dismissed
    void OnDismiss();

    // Override the event handler for mouse events to close the popup when clicking outside
    void OnMouseEvents(wxMouseEvent& event);

private:
    wxSize m_size;
    bool* isOpen;

    wxDECLARE_EVENT_TABLE();
};

