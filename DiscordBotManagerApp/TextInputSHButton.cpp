#include "TextInputSHButton.h"

TextInputSHButton::TextInputSHButton(wxWindow* parent, wxWindowID id, TextInput* input)
	: wxPanel(parent, id), isShown(false), isHovered(false), isPressed(false), m_input(input), bg(wxColour(18, 18, 18))
{
    wxInitAllImageHandlers();

    if (!show.LoadFile("assets\\icon\\show.png", wxBITMAP_TYPE_PNG)) {
        wxLogError("Couldn't load show.png");
    }

    if (!hide.LoadFile("assets\\icon\\hide.png", wxBITMAP_TYPE_PNG)) {
        wxLogError("Couldn't load hide.png");
    }

    lastShow = show;
    lastHide = hide;

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &TextInputSHButton::OnPaint, this);
    Bind(wxEVT_LEFT_UP, &TextInputSHButton::OnMouseLeftUp, this); 
    Bind(wxEVT_LEFT_DOWN, &TextInputSHButton::OnMouseLeftDown, this);
    Bind(wxEVT_ENTER_WINDOW, &TextInputSHButton::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &TextInputSHButton::OnMouseLeave, this);
}

bool TextInputSHButton::SetBackgroundColour(const wxColour& colour)
{
    return false;
}

void TextInputSHButton::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	Render(dc);
}

void TextInputSHButton::Render(wxDC& dc)
{
    wxSize size = GetClientSize();

    // Set background color
    dc.SetBrush(wxBrush(bg));

    // Set outline color
    dc.SetPen(*wxTRANSPARENT_PEN);

    // Draw background rectangle
    dc.DrawRectangle(0, 0, size.x, size.y);

    // Scale down the bitmap to the original size for antialiasing effect or if correct size keep last one used
    wxImage img;

    if (isShown && (lastShow.GetSize().x != size.x || lastShow.GetSize().y != size.y)) {
        img = show;
        img.Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
        // Direct access to pixel data
        unsigned char* data = img.GetData();

        // Apply additive color transformation while preserving alpha channel
        unsigned char hoverValue = isHovered ? 255 : 114;
        for (int i = 0; i < size.x * size.y * 3; i += 3) {
            unsigned char& r = data[i];
            unsigned char& g = data[i + 1];
            unsigned char& b = data[i + 2];

            // Apply additive color transformation (rgb(18,18,18))
            r = isHovered ? 255 : (r + hoverValue < 255) ? r + hoverValue : 255;
            g = isHovered ? 255 : (g + hoverValue < 255) ? g + hoverValue : 255;
            b = isHovered ? 255 : (b + hoverValue < 255) ? b + hoverValue : 255;
        }

    }
    else if (lastShow.GetSize().x != size.x || lastShow.GetSize().y != size.y) {
        img = hide;
        img.Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
        // Direct access to pixel data
        unsigned char* data = img.GetData();

        // Apply additive color transformation while preserving alpha channel
        unsigned char hoverValue = isHovered ? 255 : 114;
        for (int i = 0; i < size.x * size.y * 3; i += 3) {
            unsigned char& r = data[i];
            unsigned char& g = data[i + 1];
            unsigned char& b = data[i + 2];

            // Apply additive color transformation (rgb(18,18,18))
            r = isHovered ? 255 : (r + hoverValue < 255) ? r + hoverValue : 255;
            g = isHovered ? 255 : (g + hoverValue < 255) ? g + hoverValue : 255;
            b = isHovered ? 255 : (b + hoverValue < 255) ? b + hoverValue : 255;
        }

    }
    else {
        img = isShown ? lastShow : lastHide;
    }
    
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

void TextInputSHButton::OnMouseEnter(wxMouseEvent& event)
{
    isHovered = true;
    Refresh();
    event.Skip();
}

void TextInputSHButton::OnMouseLeave(wxMouseEvent& event)
{
    isHovered = false;
    isPressed = false;
    Refresh();
    event.Skip();
}

void TextInputSHButton::OnMouseLeftUp(wxMouseEvent& event)
{
    if (isPressed) {
        OnButtonClick();
    }
    Refresh();
    isPressed = false;
}

void TextInputSHButton::OnMouseLeftDown(wxMouseEvent& event)
{
    isPressed = true;
    Refresh();
    event.Skip();
}

void TextInputSHButton::OnButtonClick()
{
    isShown = !isShown;

    m_input->SetEncrypted(!isShown);
}
