#include "LabeledTextInputPanel.h"

LabeledTextInputPanel::LabeledTextInputPanel(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, 
    const wxSize& size, long style, Callback onTextChange, Callback onEnter, Validator validator)
    : wxPanel(parent, id, pos, size, style), m_textInput(this, wxID_ANY, value, wxDefaultPosition, wxDefaultSize, style, onTextChange, onEnter, validator),
    m_isEncrypted(false), m_isHovered(false), m_button(this, wxID_ANY, &m_textInput), m_label(this, wxID_ANY, value, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL),
    m_isEmpty(true), m_hoveredChild(false)
{
    // Set background color of the panel
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Set variables
    this->bg = wxColour(18, 18, 18);
    this->fg = wxColour(255, 255, 255);
    this->outline = wxColour(255, 255, 255);
    this->outlineInactive = wxColour(114, 114, 114);
    this->fontDefaultSize = m_textInput.GetFont().GetPointSize();
    this->labelFontDefaultSize = m_label.GetFont().GetPointSize();
    this->defaultPos = pos;
    this->defaultSize = size;

    // Set text colors
    m_textInput.SetColors(fg, bg, outlineInactive);

    // Setting up the label
    m_label.Show(!m_isEmpty);
    m_label.SetBackgroundColour(bg);
    m_label.SetForegroundColour(fg);

    m_textInput.Bind(wxEVT_SET_FOCUS, &LabeledTextInputPanel::OnSetFocus, this);
    m_textInput.Bind(wxEVT_KILL_FOCUS, &LabeledTextInputPanel::OnKillFocus, this);
    m_label.Bind(wxEVT_ENTER_WINDOW, &LabeledTextInputPanel::OnMouseEnterLabel, this);
    m_label.Bind(wxEVT_LEAVE_WINDOW, &LabeledTextInputPanel::OnMouseLeaveLabel, this);
    Bind(wxEVT_PAINT, &LabeledTextInputPanel::OnPaint, this);
    Bind(wxEVT_ENTER_WINDOW, &LabeledTextInputPanel::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &LabeledTextInputPanel::OnMouseLeave, this);
    Bind(wxEVT_LEFT_DOWN, &LabeledTextInputPanel::OnMouseLeftDown, this);
    Bind(wxEVT_NAVIGATION_KEY, &LabeledTextInputPanel::OnNavigationKeyPress, this);
    //
    m_button.Hide();
}

void LabeledTextInputPanel::Render(wxDC& dc)
{
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp = Utils::CreateEmptyBitmap(size);
    wxMemoryDC memDC;
    memDC.SelectObject(bmp);

    // Set the background color
    memDC.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        // Draw the rounded rectangle on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

        int outlineSize = this->m_textInput.HasFocus() ? 5 : 2;
        wxColour outlineColour = wxColour(this->m_textInput.HasFocus() || m_isHovered ? outline : outlineInactive);

        int textWidth, textHeight;
        wxFont font = m_label.GetFont();
        GetTextExtent(m_label.GetLabel(), &textWidth, &textHeight, (int*)0, (int*)0, &font);

        gc->SetBrush(wxBrush(outlineColour));
        gc->DrawRoundedRectangle(
            0, 
            textHeight, 
            size.x * 2, 
            size.y * 2 - textHeight, 
            int(size.y / 5)
        );

        gc->SetBrush(wxBrush(bg));
        gc->DrawRoundedRectangle(
            outlineSize, 
            outlineSize + textHeight,
            size.x * 2 - outlineSize * 2, 
            size.y * 2 - outlineSize * 2 - textHeight, 
            int(size.y / 5) - outlineSize
        );

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.Clear();
    dc.SetBrush(wxBrush(bg));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(0, 0, size.x, size.y);
    dc.DrawBitmap(finalBmp, 0, 0, true);

    m_label.Refresh();
}

void LabeledTextInputPanel::OnPaint(wxPaintEvent& event)
{
    if ((m_textInput.Value().size() > 0 || m_textInput.HasFocus()) && !m_label.IsShown()) m_label.Show();
    else if ((m_textInput.Value().size() == 0 && !m_textInput.HasFocus()) && m_label.IsShown()) m_label.Hide();

    // Create a device context for drawing
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void LabeledTextInputPanel::OnSetFocus(wxFocusEvent& event)
{
    event.Skip();
}

void LabeledTextInputPanel::OnKillFocus(wxFocusEvent& event)
{
    Refresh();
    event.Skip();
}

void LabeledTextInputPanel::OnMouseEnter(wxMouseEvent& event)
{
    m_isHovered = true;
    if (!m_hoveredChild) Refresh();
    m_hoveredChild = false;
    event.Skip();
}

void LabeledTextInputPanel::OnMouseEnterLabel(wxMouseEvent& event)
{
    m_isHovered = true;
    Refresh();
    event.Skip();
}

void LabeledTextInputPanel::OnMouseLeave(wxMouseEvent& event)
{
    // Get the positions and sizes
    wxPoint inputPos = m_textInput.GetPosition();
    wxSize inputSize = m_textInput.GetSize();

    wxPoint buttonPos = m_button.GetPosition();
    wxSize buttonSize = m_button.GetSize();

    wxPoint labelPos = m_label.GetPosition();
    wxSize labelSize = m_label.GetSize();
  
    // Calculate the bounding boxes
    wxRect inputRect(inputPos, inputSize);
    wxRect buttonRect(buttonPos, buttonSize);
    wxRect labelRect(labelPos, labelSize);

    // Get the mouse position
    wxPoint mousePos = event.GetPosition();

    // Check if the mouse position is within the bounding box of the text input
    if (inputRect.Contains(mousePos) || buttonRect.Contains(mousePos) || labelRect.Contains(mousePos)) {
        // Mouse is still inside the text input, do not change m_isHovere
        m_hoveredChild = true;
    }
    else {
        // Mouse is leaving the panel entirely, set m_isHovered to false with a slight delay
        m_isHovered = false;
        Refresh();
    }

    event.Skip();
}

void LabeledTextInputPanel::OnMouseLeaveLabel(wxMouseEvent& event)
{
    // Get the mouse position
    wxPoint mousePos = event.GetPosition();

    // Get size of panel
    wxSize size(GetSize());

    // Check if the mouse position is still outside the panel
    if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x > size.x || mousePos.y > size.y) {
        // Mouse has left the panel, set m_isHovered to false
        m_isHovered = false;
        Refresh();
    }

    event.Skip();
}

void LabeledTextInputPanel::OnMouseLeftDown(wxMouseEvent& event)
{
    // Explicitly set focus to the TextInput only if the mouse is clicked
    // within the TextInput bounds or a specific area you designate as focusable.
    wxRect textInputRect = m_textInput.GetRect();
    if (textInputRect.Contains(event.GetPosition())) {
        m_textInput.SetFocus();
    }
    else {
        // This prevents the panel or its children from taking focus away when clicked outside
        // but allows the event to propagate up for other uses (if not needed, you can remove event.Skip()).
        
    }
}

void LabeledTextInputPanel::OnNavigationKeyPress(wxNavigationKeyEvent& event)
{
    if (event.IsFromTab()) event.Skip();
}

void LabeledTextInputPanel::Resize(wxSize windowSize, wxSize defaultWindowSize)
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

    font = m_label.GetFont();
    font.SetPointSize(labelFontDefaultSize * windowSize.y / defaultWindowSize.y);
    m_label.SetFont(font);

    int textWidth, textHeight;
    GetTextExtent(
        m_label.GetLabel(),
        &textWidth,
        &textHeight,
        (int*)0,
        (int*)0,
        &font
    );

    m_label.SetSize(
        10 * windowSize.y / defaultWindowSize.y,
        0,
        textWidth + 8,
        textHeight
    );

    m_button.SetSize(
        inputWidth - inputHeight - 3 + textHeight / 2,
        3 + textHeight / 2,
        inputHeight - 6 - textHeight / 2,
        inputHeight - 6 - textHeight / 2
    );

    // Set the new position and size for the text input
    int charHeight = m_textInput.GetCharHeight();
    m_textInput.SetSize(
        5,
        (inputHeight - charHeight + textHeight / 2) / 2,
        inputWidth - 10 - (m_isEncrypted ? m_button.GetSize().GetWidth() + 10 : 0),
        charHeight
    );
}

void LabeledTextInputPanel::SetEncrypted(bool encrypted)
{
    m_textInput.SetEncrypted(encrypted);
    m_isEncrypted = encrypted;
    m_button.Show(encrypted);
    Refresh();
}

wxString LabeledTextInputPanel::GetValue() const
{
    return this->m_textInput.Value();
}

void LabeledTextInputPanel::SetValue(wxString value)
{
    this->m_textInput.Value(value);
}

void LabeledTextInputPanel::SetFont(wxFont font)
{
    m_textInput.SetFont(font);
    fontDefaultSize = font.GetPointSize();
    Refresh();
}

void LabeledTextInputPanel::SetLabelFont(wxFont font)
{
    m_label.SetFont(font);
    labelFontDefaultSize = font.GetPointSize();
    Refresh();
}

bool LabeledTextInputPanel::SetBackgroundColour(const wxColour& colour)
{
    try {
        bg = colour;
        m_textInput.SetColors(fg, bg, outlineInactive);
        m_label.SetBackgroundColour(bg);
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool LabeledTextInputPanel::SetForegroundColour(const wxColour& colour)
{
    try {
        fg = colour;
        m_textInput.SetColors(fg, bg, outlineInactive);
        m_label.SetForegroundColour(fg);
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool LabeledTextInputPanel::SetOutlineColour(const wxColour& colour)
{
    try {
        outline = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool LabeledTextInputPanel::SetInactiveOutlineColour(const wxColour& colour)
{
    try {
        outlineInactive = colour;
        m_textInput.SetColors(fg, bg, outlineInactive);
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}
