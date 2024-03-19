#pragma once

#include "Utils.h"
#include "TextInput.h"
#include "TextInputSHButton.h"
#include "Label.h"

/// <summary>
/// This class creates text input that is already labeled.
/// In addition it can be encrypted (used for entering password).
/// </summary>
class LabeledTextInputPanel : public wxPanel
{
public:
    using Callback = std::function<void(wxString value)>;

    /// <summary>
    /// Constructor for LabaledTextInputPanel class.
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
    /// <param name="bg">Color of the background.</param>
    /// <param name="fg">Color of the text.</param>
    /// <param name="outline">Color of the active outline.</param>
    /// <param name="outlineInactive">Color of the inactive outline.</param>
    LabeledTextInputPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& value = wxEmptyString,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxTE_PROCESS_ENTER,
        Callback onTextChange = [](wxString value = "") {}, Callback onEnter = [](wxString value = "") {});

    /// <summary>
    /// Resizes the window in relation to window size.
    /// </summary>
    /// <param name="windowSize">Current window size.</param>
    /// <param name="defaultWindowSize">Size of the window that it is created with.</param>
    virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

    /// <summary>
    /// Function that sets encryption.
    /// </summary>
    /// <param name="encrypted">Variable that sets encryption on (true) or off (false).</param>
    virtual void SetEncrypted(bool encrypted);

    /// <summary>
    /// Getter function for Value.
    /// </summary>
    /// <returns>Value in input.</returns>
    virtual wxString GetValue() const;

    /// <summary>
    /// Setter function for value.
    /// </summary>
    /// <param name="value">String that will be put inside the input.</param>
    virtual void SetValue(wxString value);

    /// <summary>
    /// Setter function for the font.
    /// </summary>
    /// <param name="font">Font that will be set.</param>
    virtual void SetFont(wxFont font);

    /// <summary>
    /// Setter function for the label font.
    /// </summary>
    /// <param name="font">Font that will be set.</param>
    virtual void SetLabelFont(wxFont font);

    virtual bool SetBackgroundColour(const wxColour& bg);
    virtual bool SetForegroundColour(const wxColour& bg);
    virtual bool SetOutlineColour(const wxColour& bg);
    virtual bool SetInactiveOutlineColour(const wxColour& bg);

    TextInput m_textInput;
protected:
    /// <summary>
    /// Inner function that draws the element.
    /// </summary>
    /// <param name="dc">Drawing component from wxWidgets.</param>
    virtual void Render(wxDC& dc);

    /// <summary>
    /// Repaints the window.
    /// </summary>
    /// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
    virtual void OnPaint(wxPaintEvent& event);

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
    /// Function that is run whenever mouse enters the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseEnter(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever mouse enters the label.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseEnterLabel(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever mouse leaves the element.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseLeave(wxMouseEvent& event);

    /// <summary>
    /// Function that is run whenever mouse leaves the label.
    /// </summary>
    /// <param name="event">Event passed to the function.</param>
    virtual void OnMouseLeaveLabel(wxMouseEvent& event);


    virtual void OnMouseLeftDown(wxMouseEvent& event);

    virtual void OnNavigationKeyPress(wxNavigationKeyEvent& event);

    Label m_label;
    TextInputSHButton m_button;
    wxColour fg;
    wxColour bg;
    wxColour outline;
    wxColour outlineInactive;
    wxSize defaultSize;
    wxPoint defaultPos;
    int fontDefaultSize;
    int labelFontDefaultSize;
    bool m_isHovered;
    bool m_isEncrypted;
    bool m_isEmpty;
    bool m_hoveredChild;
};

