#pragma once
#include "ScrollControl.h"

/// <summary>
/// Inner class of ScrollPanel. Draws button-like object.
/// </summary>
class ScrollButton : public ScrollControl {
public:
    using ButtonCallback = std::function<void(wxString item)>;

    /// <summary>
    /// Contructor for ScrollButton class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that Image class will be in.</param>
    /// <param name="pos">Position where Image will be drawn.</param>
    /// <param name="size">Size of the popup.</param>
    /// <param name="label">Name of the button.</param>
    /// <param name="callback">Function run on press.</param>
    ScrollButton(wxWindow* parent, wxPoint pos, wxSize size, const wxString& label, ButtonCallback callback = [](wxString item = "") {})
        : ScrollControl(parent, pos, size), m_label(label), callback(callback) {}

    /// <summary>
    /// Repaints the button.
    /// </summary>
    /// <param name="gc">wxGraphicsContext provided by the parent.</param>
    void Draw(wxGraphicsContext* gc) override;

    /// <summary>
    /// Function that is run whenever button is clicked.
    /// (Though you need to add event functionality yourself)
    /// </summary>
    void OnClick() override;

private:
    wxString m_label;
    wxFont font = wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
    ButtonCallback callback;
};
