#include "TextInput.h"

TextInput::TextInput(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size,
    long style, const wxValidator& validator, const wxString& name, wxWindow* m_parent, wxWindow* m_panel)
    : wxTextCtrl(parent, id, "", pos, size, style | wxBORDER_NONE, validator, name), m_parent(m_parent), m_hasFocus(false), parent(parent)
{
    this->fg = wxColour(255, 255, 255);
    this->fgInactive = wxColour(114, 114, 114);
    this->bg = wxColour(18, 18, 18);

    // Set background color
    SetBackgroundColour(this->bg);

    // Set text color
    SetForegroundColour(this->fgInactive);

    if (m_panel) {
        m_panel->Bind(wxEVT_LEFT_DOWN, &TextInput::OnLeftDown, this);
    }
    
    this->style = GetWindowStyleFlag();
    this->value = "";
    this->defaultValue = value;
    this->m_isEncrypted = false;
    SetValue(defaultValue);

    // Bind event to handle focus behavior
    Bind(wxEVT_SET_FOCUS, &TextInput::OnSetFocus, this);
    Bind(wxEVT_KILL_FOCUS, &TextInput::OnKillFocus, this);
    Bind(wxEVT_TEXT, &TextInput::OnTextChange, this);
}

void TextInput::OnLeftDown(wxMouseEvent& event)
{
    // Check if the click occurred outside of the input control
    wxPoint pos = event.GetPosition();
    wxRect rect = GetScreenRect();
    if (!rect.Contains(pos))
    {
        // Set focus to another window to ensure that the input control loses focus
        if (m_parent)
        {
            m_parent->SetFocus();
        }
    }
    event.Skip();
}

wxRect TextInput::GetScreenRect() const
{
    wxRect rect = GetRect();
    ClientToScreen(&rect.x, &rect.y);
    return rect;
}

void TextInput::OnTextChange(wxCommandEvent& event)
{
    wxString input = event.GetString();

    // If the input matches the default value, return
    if (input == defaultValue) {
        return;
    }

    wxString displayText;

    // Save cursor position
    long start, end;
    GetSelection(&start, &end);

    if (!m_isEncrypted) {
        value = input;
        displayText = value;
    }
    else {
        // Calculate the size difference between the displayed text and the value
        int sizeDifference = value.size() - input.size();

        // Determine the insertion index based on the cursor position
        int insertionIndex = end;

        for (int i = 0; i < sizeDifference; i++) value = value.SubString(0, end - 1) + value.SubString(end + 1, value.size() - 1);
        for (int i = value.size(), j = 0; i < input.size(); i++, j++) {
            value = value.SubString(0, end + sizeDifference - 1) + input.SubString(end - j - 1, end - j - 1) + value.SubString(end + sizeDifference, value.size() - 1);
        }
        for (int i = 0; i < input.size(); i++) {
            if (input.SubString(i, i) != wxString(wxT("\x25cf"))) {
                if (i == 0) {
                    value = input.SubString(i, i) + value.SubString(i + 1, value.size() - 1);
                }
                else if (i == input.size() - 1) {
                    value = value.SubString(0, i - 1) + input.SubString(i, i);
                }
                else {
                    value = value.SubString(0, i - 1) + input.SubString(i, i) + value.SubString(i + 1, value.size() - 1);
                }
            }
        }

        // Encrypt the input for display
        wxString encryptedText(value.length(), wxT('\x25cf'));
        displayText = encryptedText;
    }
    // Update the control's displayed text
    ChangeValue(displayText);

    // Restore cursor position
    SetInsertionPoint(start);
  
    // Log the value for debugging
    /*if (!value.empty()) {
        wxLogDebug(value);
    }*/
}

void TextInput::SetEncrypted(bool encrypted)
{
    m_isEncrypted = encrypted;

    if (m_isEncrypted && value.size() > 0) {
        SetValue(wxString(value.length(), wxT('\x25cf')));
    }
    else if (!m_isEncrypted && value.size() > 0) {
        SetValue(value);
    }
}

wxString TextInput::Value() const
{
    return value;
}

void TextInput::Value(wxString value)
{
    this->value = value;
    if (value != "") {
        SetForegroundColour(fg);
        SetValue(value);
    }
    Refresh();
}

void TextInput::SetColors(wxColour fg, wxColour bg, wxColour fgInactive)
{
    this->fg = fg;
    this->fgInactive = fgInactive;
    this->bg = bg;
}

void TextInput::OnSetFocus(wxFocusEvent& event)
{
    m_hasFocus = true;
    if (this->value.size() == 0) {
        SetValue(value);
        SetForegroundColour(fg);
    }
    parent->Refresh();
    //Refresh();
    event.Skip();
}

void TextInput::OnKillFocus(wxFocusEvent& event)
{
    m_hasFocus = false;
    if (this->value.size() == 0) {
        SetValue(defaultValue);
        SetForegroundColour(fgInactive);
        parent->Refresh();
    }
    //Refresh();
    event.Skip();
}

