#include "RoundedItem.h"

RoundedItem::RoundedItem(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, ButtonCallback callback, wxString label, bool showIcon, wxString iconPath, bool selected, wxFont font)
    : bg(wxColour(0,0,0)), m_showIcon(showIcon), m_isSelected(false), m_isHovered(false), m_isPressed(false),
    wxPanel(parent, id, pos, size), m_isShown(false), fg(wxColour(114, 114, 114)), selected(wxColour(255, 255, 255)), 
    m_callback(callback), hover(wxColour(196, 196, 196)), m_label(label), m_hint(nullptr), defaultFont(font.GetPointSize())
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetFont(font);
    if (m_showIcon) {
        if (!icon.LoadFile(iconPath, wxBITMAP_TYPE_PNG)) {
            wxLogError("Couldn't load icon.");
        }

        lastIcon = icon;
    }

    SetSelected(selected);
}

bool RoundedItem::SetBackgroundColour(const wxColour& colour)
{
    try {
        bg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool RoundedItem::SetForegroundColour(const wxColour& colour)
{
    try {
        fg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool RoundedItem::SetHoverColour(const wxColour& colour)
{
    try {
        hover = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool RoundedItem::SetSelectedColour(const wxColour& colour)
{
    try {
        selected = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

void RoundedItem::SetSelected(const bool& state)
{
    this->m_isSelected = state;
}

bool RoundedItem::GetSelected() const
{
    return m_isSelected;
}

void RoundedItem::UpdateFontSize(double mod)
{
    wxFont buffer = GetFont();
    buffer.SetPointSize((int)(mod * defaultFont));
    SetFont(buffer);
}

void RoundedItem::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void RoundedItem::Render(wxDC& dc)
{
    wxSize size = GetClientSize();
    wxColour fgColour = m_isSelected ? selected : (m_isHovered ? hover : fg);

    if (m_showIcon) {
        // Set background color
        dc.SetBrush(wxBrush(bg));

        // Set outline color
        dc.SetPen(*wxTRANSPARENT_PEN);

        // Draw background rectangle
        dc.DrawRectangle(0, 0, size.x, size.y);

        // Scale down the bitmap to the original size for antialiasing effect or if correct size keep last one used
        wxImage img;

        if (icon.GetSize().x != size.x || icon.GetSize().y != size.y) {
            img = icon;
            img.Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
            // Direct access to pixel data
            unsigned char* data = img.GetData();

            // Apply additive color transformation while preserving alpha channel
            unsigned char hoverValue = fgColour.GetRed();
            for (int i = 0; i < size.x * size.y * 3; i += 3) {
                unsigned char& r = data[i];
                unsigned char& g = data[i + 1];
                unsigned char& b = data[i + 2];

                // Apply additive color transformation (rgb(18,18,18))
                r = (r + hoverValue < 255) ? r + hoverValue : 255;
                g = (g + hoverValue < 255) ? g + hoverValue : 255;
                b = (b + hoverValue < 255) ? b + hoverValue : 255;
            }

        }
        else {
            img = icon;
        }

        wxBitmap finalBmp(img);

        // Draw the bitmap on the device context
        dc.DrawBitmap(finalBmp, 0, 0, true);
    }
    else {
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

            gc->SetBrush(wxBrush(fgColour));
            gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, 24);

            delete gc;
        }

        // Scale down the bitmap to the original size for antialiasing effect
        wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
        wxBitmap finalBmp(img);

        // Draw the bitmap on the device context
        dc.DrawBitmap(finalBmp, 0, 0, true);
    }
}

void RoundedItem::OnMouseEnter(wxMouseEvent& event)
{
    m_isHovered = true;

    
    wxSize extent = GetTextExtent(m_label) * 1.1;
    m_hint = new Hint(this, m_label);
    m_hint->SetPosition(GetScreenPosition() + wxPoint(GetSize().x + 4, (GetSize().y - extent.y) / 2));
    m_hint->SetSize(extent);
    m_hint->SetFont(GetFont());
    m_hint->Popup();

    Refresh();
}

void RoundedItem::OnMouseLeave(wxMouseEvent& event)
{
    m_isHovered = false;
    m_isPressed = false;
    if (m_hint) {
        m_hint->Dismiss();
        delete m_hint;
    }
    Refresh();
}

void RoundedItem::OnMouseLeftUp(wxMouseEvent& event)
{
    if (m_isPressed) {

        if (m_callback)
            if (m_callback()) m_isSelected = true;
   
        Refresh();
    }
}

void RoundedItem::OnMouseLeftDown(wxMouseEvent& event)
{
    m_isPressed = true;
    Refresh();
}

BEGIN_EVENT_TABLE(RoundedItem, wxPanel)
    EVT_PAINT(RoundedItem::OnPaint)
    EVT_LEFT_UP(RoundedItem::OnMouseLeftUp)
    EVT_LEFT_DOWN(RoundedItem::OnMouseLeftDown)
    EVT_LEAVE_WINDOW(RoundedItem::OnMouseLeave)
    EVT_ENTER_WINDOW(RoundedItem::OnMouseEnter)
END_EVENT_TABLE()