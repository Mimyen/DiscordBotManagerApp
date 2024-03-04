#include "RoundedButton.h"

RoundedButton::RoundedButton(wxWindow* parent, const wxString& label, const wxPoint& position, 
    const wxSize& size, const wxColour& colour, const wxColour& clicked, const wxColour& bg, 
    const wxColour& fg, ButtonCallback callback, bool drawOutline, const wxColour& outline, unsigned int outlineSize)
	: wxPanel(parent, wxID_ANY, position, size), m_label(label), m_hovered(false), 
    m_clicked(false), m_hold(false), outlineSize(outlineSize), drawOutline(drawOutline)
{
    // Bind events
    Bind(wxEVT_PAINT, &RoundedButton::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &RoundedButton::OnMouseLeftUp, this);
    Bind(wxEVT_LEFT_DOWN, &RoundedButton::OnMouseLeftDown, this);
    Bind(wxEVT_ENTER_WINDOW, &RoundedButton::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &RoundedButton::OnMouseLeave, this);
    Bind(wxEVT_BUTTON, &RoundedButton::OnButtonClick, this);

    // Set variables
    this->colour = colour;
    this->bg = bg;
    this->fg = fg;
    this->clicked = clicked;
    this->outline = outline;
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

void RoundedButton::SetLabel(const wxString& label)
{
    m_label = label;
    Refresh();
}

void RoundedButton::SetFont(wxFont font)
{
    this->font = font;
    this->fontDefaultSize = font.GetPointSize();
}

void RoundedButton::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int buttonWidth = defaultSize.x * windowSize.x / defaultWindowSize.x; 
    int buttonHeight = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int buttonX = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int buttonY = defaultPos.y * windowSize.y / defaultWindowSize.y;
    int fontSize = fontDefaultSize * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the button
    SetSize(buttonX, buttonY, buttonWidth, buttonHeight);
    this->font.SetPointSize(fontSize);
    radius = GetSize().y;

    Refresh();
}

void RoundedButton::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void RoundedButton::Render(wxDC& dc)
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

        // Draw rounded rectangle
        if (!drawOutline) {
            gc->SetBrush(wxBrush(m_hold ? clicked : colour));
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

void RoundedButton::OnMouseEnter(wxMouseEvent& event)
{
    m_hovered = true;
    Increase();
    event.Skip();
}

void RoundedButton::OnMouseLeave(wxMouseEvent& event)
{
    if (m_hovered) {
        if (!m_hold) Reduce();
        else Refresh();
        m_hovered = false;
        m_clicked = false;
        m_hold = false; 
        event.Skip();
    }
}


void RoundedButton::OnMouseLeftUp(wxMouseEvent& event)
{
    if (m_clicked) {
        m_clicked = false;
        m_hold = false;
        Increase();
        wxCommandEvent evt(wxEVT_BUTTON, GetId());
        GetEventHandler()->ProcessEvent(evt);
    }
    event.Skip();
}

void RoundedButton::OnMouseLeftDown(wxMouseEvent& event)
{

    m_clicked = true;
    m_hold = true;
    Reduce();
    event.Skip();
}

void RoundedButton::Reduce()
{
    SetSize(GetSize() - wxSize(2, 2));
    SetPosition(GetPosition() + wxPoint(1, 1));
    radius -= 2;
    Refresh();
}

void RoundedButton::Increase()
{
    SetSize(GetSize() + wxSize(2, 2));
    SetPosition(GetPosition() - wxPoint(1, 1));
    radius += 2;
    Refresh();
}

void RoundedButton::OnButtonClick(wxCommandEvent& event)
{
    if (m_callback) m_callback();
}