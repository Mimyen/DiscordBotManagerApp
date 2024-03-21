#include "SimpleRoundedButton.h"

SimpleRoundedButton::SimpleRoundedButton(wxWindow* parent, const wxString& label, const wxPoint& position,
    const wxSize& size, ButtonCallback callback, bool drawOutline, unsigned int outlineSize)
    : wxPanel(parent, wxID_ANY, position, size), m_label(label), m_hovered(false),
    m_clicked(false), m_hold(false), outlineSize(outlineSize), drawOutline(drawOutline), m_callbackRunning(false)
{
    // Bind events
    Bind(wxEVT_PAINT, &SimpleRoundedButton::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &SimpleRoundedButton::OnMouseLeftUp, this);
    Bind(wxEVT_LEFT_DOWN, &SimpleRoundedButton::OnMouseLeftDown, this);
    Bind(wxEVT_ENTER_WINDOW, &SimpleRoundedButton::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &SimpleRoundedButton::OnMouseLeave, this);


    // Set variables
    this->colour = wxColour(26, 188, 156);
    this->bg = wxColour(18, 18, 18);
    this->fg = wxColour(0, 0, 0);
    this->clicked = wxColour(17, 120, 99);
    this->outline = wxColour(255, 255, 255);
    this->radius = size.y;
    this->defaultSize = size;
    this->defaultPos = position;
    this->font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    this->fontDefaultSize = font.GetPointSize();

    // Set bg colour
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(bg);

    // Set minimum size for the button
    SetMinSize(size);

    // Fit the panel to its contents
    Fit();

    m_callback = callback;
}

void SimpleRoundedButton::SetLabel(const wxString& label)
{
    m_label = label;
    Refresh();
}

void SimpleRoundedButton::SetFont(wxFont font)
{
    this->font = font;
    this->fontDefaultSize = font.GetPointSize();
}

void SimpleRoundedButton::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int buttonWidth = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int buttonHeight = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int buttonX = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int buttonY = defaultPos.y * windowSize.y / defaultWindowSize.y;
    int fontSize = fontDefaultSize * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the button
    this->font.SetPointSize(fontSize);
    radius = buttonHeight;

    SetSize(buttonX, buttonY, buttonWidth, buttonHeight);
}

bool SimpleRoundedButton::SetBackgroundColour(const wxColour& colour)
{
    try {
        bg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool SimpleRoundedButton::SetForegroundColour(const wxColour& colour)
{
    try {
        fg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool SimpleRoundedButton::SetOutlineColour(const wxColour& colour)
{
    try {
        outline = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool SimpleRoundedButton::SetPressedColour(const wxColour& colour)
{
    try {
        clicked = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool SimpleRoundedButton::SetColour(const wxColour& colour)
{
    try {
        this->colour = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

void SimpleRoundedButton::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void SimpleRoundedButton::Render(wxDC& dc)
{
    dc.Clear();
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

        // Draw rounded rectangle
        if (!drawOutline) {
            gc->SetBrush(wxBrush(m_hold ? clicked : (m_hovered ? wxColour((clicked.Red() + colour.Red()) / 2, (clicked.Green() + colour.Green()) / 2, (clicked.Blue() + colour.Blue()) / 2) : colour)));
            gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, radius);
        }
        else {
            gc->SetBrush(wxBrush(outline));
            gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, radius);
            gc->SetBrush(wxBrush(m_hold ? clicked : colour));
            gc->DrawRoundedRectangle(outlineSize, outlineSize, size.x * 2 - outlineSize * 2, size.y * 2 - outlineSize * 2, radius - outlineSize);
        }

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);

    // Draw the label text
    dc.SetFont(font);
    dc.SetTextForeground(fg);
    wxCoord textWidth, textHeight;
    dc.GetTextExtent(m_label, &textWidth, &textHeight);
    dc.DrawText(m_label, (size.x - textWidth) / 2, (size.y - textHeight) / 2);
}

void SimpleRoundedButton::OnMouseEnter(wxMouseEvent& event)
{
    m_hovered = true;
    Refresh();
    event.Skip();
}

void SimpleRoundedButton::OnMouseLeave(wxMouseEvent& event)
{
    if (m_hovered) {
        Refresh();
        m_hovered = false;
        m_clicked = false;
        m_hold = false;
        event.Skip();
    }
}


void SimpleRoundedButton::OnMouseLeftUp(wxMouseEvent& event)
{
    if (m_clicked) {
        m_clicked = false;
        m_hold = false;
        Refresh();
        event.Skip();
        if (m_callback && !m_callbackRunning.exchange(true)) {
            std::thread([this]() {
                m_callback();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                m_callbackRunning = false;

                }).detach();
        }
    }
    else event.Skip();
}

void SimpleRoundedButton::OnMouseLeftDown(wxMouseEvent& event)
{

    m_clicked = true;
    m_hold = true;
    Refresh();
    event.Skip();
}