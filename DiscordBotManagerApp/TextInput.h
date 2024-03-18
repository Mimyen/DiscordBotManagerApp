#pragma once

#include "Utils.h"

/// <summary>
/// This class is inner class of TextInputPanel component. 
/// It's responsible for the input itself.
/// </summary>
class TextInput : public wxTextCtrl
{
public:
    /// <summary>
    /// Constructor for TextInput class.
    /// </summary>
    /// <param name="parent">Pointer to cointainer that component will be in.</param>
    /// <param name="id">Id of the object, useable for making calls.</param>
    /// <param name="value">Default value displayed when input is unfocused and empty.</param>
    /// <param name="pos">Position where component will be drawn.</param>
    /// <param name="size">Size of the component.</param>
    /// <param name="style">Style for the input.</param>
    /// <param name="validator">Validates the text.</param>
    /// <param name="name">Name of the component.</param>
    /// <param name="m_parent">Object passed to TextInput inner class.</param>
    /// <param name="m_panel">Object that will be tracked.</param>
    TextInput(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxTE_PROCESS_ENTER, const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxTextCtrlNameStr, wxWindow* m_parent = nullptr, wxWindow* m_panel = nullptr);

    /// <summary>
    /// Setter function for colors.
    /// </summary>
    /// <param name="fg">Color of the font.</param>
    /// <param name="fg">Color of the background.</param>
    /// <param name="fg">Color of the default text.</param>
    virtual void SetColors(wxColour fg, wxColour bg, wxColour fgInactive);

    /// <summary>
    /// Function that sets encryption.
    /// </summary>
    /// <param name="encrypted">Variable that sets encryption on (true) or off (false).</param>
    virtual void SetEncrypted(bool encrypted);

    /// <summary>
    /// Getter function for Value.
    /// </summary>
    /// <returns>Value in input.</returns>
    virtual wxString Value() const;

    /// <summary>
    /// Setter function for value.
    /// </summary>
    /// <param name="value">String that will be put inside the input.</param>
    virtual void Value(wxString value);

    bool m_isEncrypted;

protected:
    /// <summary>
    /// Function that is run whenever mouse button is pressed whilst over the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnLeftDown(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever focus is set to the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnSetFocus(wxFocusEvent& event);

    /// <summary>
    /// Function that is run whenever focus is lost from the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnKillFocus(wxFocusEvent& event);

    /// <summary>
    /// Function that is run whenever text is changed.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnTextChange(wxCommandEvent& event);

    /// <summary>
    /// Getter function for Rect.
    /// </summary>
    /// <returns>Rect of the component</returns>
    virtual wxRect GetScreenRect() const;

    wxWindow* m_parent;
    wxWindow* parent;
    wxString defaultValue;
    wxString value;
    wxColour fg;
    wxColour fgInactive;
    wxColour bg;
    bool m_hasFocus;
    long style;
};

