#include "ColorPicker.h"

ColorPicker::ColorPicker(wxWindow* parent, wxPoint pos, wxSize size, Callback onColorChange)
    : bg(wxColour(18, 18, 18)), m_r(26), m_g(188), m_b(156),
    wxPanel(parent, wxID_ANY, pos, size), defaultSize(size), defaultPos(pos),
    m_hovered(false), m_clicked(false), m_hold(false), m_callback(onColorChange),
    outlineActive(wxColour(255, 255, 255)), outlineInactive(wxColour(114, 114, 114)),
    m_popup(nullptr)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void ColorPicker::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int objectX = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int objectY = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int objectWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int objectHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the object
    SetSize(objectWidth, objectHeight, objectX, objectY);
}

bool ColorPicker::SetBackgroundColour(const wxColour& colour)
{
    try {
        bg = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool ColorPicker::SetOutlineActiveColour(const wxColour& colour)
{
    try {
        outlineActive = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

bool ColorPicker::SetOutlineInactiveColour(const wxColour& colour)
{
    try {
        outlineInactive = colour;
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}

std::vector<int> ColorPicker::GetRGB() const
{
    std::vector<int> RGB;
    RGB.emplace_back(m_r);
    RGB.emplace_back(m_g);
    RGB.emplace_back(m_b);
    return RGB;
}

void ColorPicker::Render(wxDC& dc)
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

        gc->SetBrush(wxBrush(m_hovered ? outlineActive : outlineInactive));
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, size.y / 4);

        gc->SetBrush(wxBrush(wxColour(m_r, m_g, m_b)));
        gc->DrawRoundedRectangle(2, 2, size.x * 2 - 4, size.y * 2 - 4, size.y / 4);

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

void ColorPicker::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	Render(dc);
}

void ColorPicker::OnMouseLeftUp(wxMouseEvent& event)
{
    if (m_clicked) {
        m_clicked = false;
        m_hold = false;
        Refresh();
        m_popup = new ColorPickerPopup(
            this, 
            m_r, 
            m_g, 
            m_b, 
            wxID_ANY, 
            wxPoint(
                wxGetTopLevelParent(this)->GetScreenPosition().x + wxGetTopLevelParent(this)->GetSize().x / 4,
                wxGetTopLevelParent(this)->GetScreenPosition().y + wxGetTopLevelParent(this)->GetSize().y / 4
            ), 
            wxGetTopLevelParent(this)->GetSize() / 2, 
            m_callback
        );
        m_popup->ShowModal();
        LDC(m_popup->GetSize().x);
        LDC(m_popup->GetSize().y);
        LDC(m_popup->GetPosition().x);
        LDC(m_popup->GetPosition().y);
        m_popup->Refresh();
        m_popup->Show();
        event.Skip();
    }
    else event.Skip();
}

void ColorPicker::OnMouseLeftDown(wxMouseEvent& event)
{
    m_clicked = true;
    m_hold = true;
    Refresh();
    event.Skip();

}

void ColorPicker::OnMouseEnter(wxMouseEvent& event)
{
    m_hovered = true;
    Refresh();
    event.Skip();
}

void ColorPicker::OnMouseLeave(wxMouseEvent& event)
{
    if (m_hovered) {
        m_hovered = false;
        m_clicked = false;
        m_hold = false;
        Refresh();
        event.Skip();
    }
}

wxBEGIN_EVENT_TABLE(ColorPicker, wxPanel)
	EVT_PAINT(ColorPicker::OnPaint)
	EVT_LEFT_DOWN(ColorPicker::OnMouseLeftDown)
	EVT_LEFT_UP(ColorPicker::OnMouseLeftUp)
	EVT_LEAVE_WINDOW(ColorPicker::OnMouseLeave)
	EVT_ENTER_WINDOW(ColorPicker::OnMouseEnter)
wxEND_EVENT_TABLE()