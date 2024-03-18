#pragma once

#include "ScrollPanel.h"

/// <summary>
/// Inner class of DropdownMenu. Creates a popup with menu options.
/// </summary>
class MenuPopup : public wxPopupTransientWindow
{
public:
    using ButtonCallback = std::function<void(wxString item)>;

    /// <summary>
    /// Contructor for MenuPopup class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that Image class will be in.</param>
    /// <param name="id">Id of the object, useable for making calls.</param>
    /// <param name="size">Size of the popup.</param>
    /// <param name="open">Pointer to parent variable isOpen.</param>
    /// <param name="options">Options that will be available in the popup.</param>
    /// <param name="selectedOption">Pointer to parent variable selectedOption.</param>
    /// <param name="callback">Function run to set selectedOption.</param>
    MenuPopup(wxWindow* parent, const wxSize& size, bool* open = nullptr, std::vector<wxString> options = std::vector<wxString>(), 
        wxString* selectedOption = nullptr, ButtonCallback callback = [](wxString item = "") {}, wxFont font = wxFont());

private:
    /// <summary>
    /// Repaints the window.
    /// </summary>
    /// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
    void OnPaint(wxPaintEvent& event);

    /// <summary>
    /// Is run when popup is being clsoed.
    /// </summary>
    void OnDismiss();

    /// <summary>
    /// Repaints the window.
    /// </summary>
    /// <param name="event">wxMouseEvent that contains data about mouse.</param>
    void OnMouseEvents(wxMouseEvent& event);

    wxSize m_size;
    bool* isOpen;
    ScrollPanel* scrollPanel;

    wxDECLARE_EVENT_TABLE();
};

