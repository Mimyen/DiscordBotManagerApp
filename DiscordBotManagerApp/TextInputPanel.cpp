#include "TextInputPanel.h"

TextInputPanel::TextInputPanel(wxWindow* parent, wxWindowID id, const wxString& value,
    const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name, 
    wxWindow* m_parent, wxColour bg, wxColour fg, wxColour outline, wxColour outlineInactive)
    : wxPanel(parent, id, pos, size, style, name), m_textInput(this, wxID_ANY, value, wxDefaultPosition, wxDefaultSize, style, validator, wxTextCtrlNameStr, m_parent, parent),
    m_isEncrypted(false), m_isHovered(false), m_button(this, wxID_ANY, &m_textInput)
{
    // Set background color of the panel
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(bg);

    // Set text colors
    m_textInput.SetColors(fg, bg, outlineInactive);

    // Set variables
    this->bg = bg;
    this->fg = fg;
    this->outline = outline;
    this->outlineInactive = outlineInactive;
    this->fontDefaultSize = m_textInput.GetFont().GetPointSize();
    this->defaultPos = pos;
    this->defaultSize = size;
    this->radius = 10;

    // Set up custom look
    m_textInput.Bind(wxEVT_SET_FOCUS, &TextInputPanel::OnSetFocus, this);
    m_textInput.Bind(wxEVT_KILL_FOCUS, &TextInputPanel::OnKillFocus, this);
    Bind(wxEVT_PAINT, &TextInputPanel::OnPaint, this);
    Bind(wxEVT_ENTER_WINDOW, &TextInputPanel::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &TextInputPanel::OnMouseLeave, this);

    m_button.Hide();
}

void TextInputPanel::Render(wxDC& dc)
{
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp(size * 2);
    wxMemoryDC memDC;
    memDC.SelectObject(bmp);

    // Set the background color
    memDC.SetBackground(wxBrush(bg));
    memDC.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        // Draw the rounded rectangle on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

        int outlineSize = this->m_textInput.HasFocus() ? 5 : 2;
        wxColour outlineColour = wxColour(this->m_textInput.HasFocus() || m_isHovered ? outline : outlineInactive);

        gc->SetBrush(wxBrush(outlineColour));
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, radius);
        gc->SetBrush(wxBrush(bg));
        gc->DrawRoundedRectangle(outlineSize, outlineSize, size.x * 2 - outlineSize * 2, size.y * 2 - outlineSize * 2, radius - outlineSize);

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

void TextInputPanel::OnPaint(wxPaintEvent& event)
{
    // Create a device context for drawing
    wxAutoBufferedPaintDC dc(this); 
    Render(dc);
}

void TextInputPanel::OnSetFocus(wxFocusEvent& event)
{
    Refresh();
    event.Skip();
}

void TextInputPanel::OnKillFocus(wxFocusEvent& event)
{
    Refresh();
    event.Skip();
}

void TextInputPanel::OnMouseEnter(wxMouseEvent& event)
{
    m_isHovered = true;
    Refresh();
    event.Skip();
}

void TextInputPanel::OnMouseLeave(wxMouseEvent& event)
{
    // Get the position and size of the text input relative to the panel
    wxPoint inputPos = m_textInput.GetPosition();
    wxSize inputSize = m_textInput.GetSize();

    wxPoint buttonPos = m_button.GetPosition();
    wxSize buttonSize = m_button.GetSize();

    // Calculate the bounding box of the text input relative to the panel
    wxRect inputRect(inputPos, inputSize);
    wxRect buttonRect(buttonPos, buttonSize);

    // Get the mouse position
    wxPoint mousePos = event.GetPosition();

    // Check if the mouse position is within the bounding box of the text input
    if (inputRect.Contains(mousePos)) {
        // Mouse is still inside the text input, do not change m_isHovered
    }
    else if (buttonRect.Contains(mousePos)) {

    }
    else {
        // Mouse is leaving the panel entirely, set m_isHovered to false with a slight delay
        m_isHovered = false;
        Refresh();
    }

    event.Skip();
}

void TextInputPanel::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate the new width and height for the panel
    int inputWidth = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int inputHeight = defaultSize.y * windowSize.y / defaultWindowSize.y;

    // Calculate the new X and Y position for the panel
    int inputX = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int inputY = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Calculate the font size based on the window size
    int fontSize = fontDefaultSize * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the panel
    SetSize(inputX, inputY, inputWidth, inputHeight);

    // Set the font size for the text input
    wxFont font = m_textInput.GetFont();
    font.SetPointSize(fontSize);
    m_textInput.SetFont(font);

    m_button.SetSize(inputWidth - inputHeight - 3, 3, inputHeight - 6, inputHeight - 6);

    // Set the new position and size for the text input
    int charHeight = m_textInput.GetCharHeight();
    m_textInput.SetSize(3, (inputHeight - charHeight) / 2, inputWidth - 6 - (m_isEncrypted ? m_button.GetSize().GetWidth() + 6 : 0), charHeight);

    // Refresh the panel
    Refresh();
}

void TextInputPanel::SetEncrypted(bool encrypted)
{
    m_textInput.SetEncrypted(encrypted);
    m_isEncrypted = encrypted;
    m_button.Show(encrypted);
    Refresh();
}

wxString TextInputPanel::GetValue() const
{
    return this->m_textInput.Value();
}

void TextInputPanel::SetValue(wxString value)
{
    this->m_textInput.Value(value);
}

void TextInputPanel::SetFont(wxFont font)
{
    m_textInput.SetFont(font);
    fontDefaultSize = font.GetPointSize();
    Refresh();
}