#include "Button.h"

Button::Button(wxWindow* parent, const wxString& imageName, const wxString& hoverImageName, const wxString& clickedImageName,
    const wxPoint& pos, const wxSize& size, unsigned int id)
    : wxControl(parent, id, pos, size, wxNO_BORDER), m_imageName(imageName), m_hoverImageName(hoverImageName),
    m_clickedImageName(clickedImageName), m_hovered(false), m_clicked(false)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Load images
    wxImage img1(m_imageName, wxBITMAP_TYPE_PNG);
    wxImage img2(m_hoverImageName, wxBITMAP_TYPE_PNG);
    wxImage img3(m_clickedImageName, wxBITMAP_TYPE_PNG);

    // Convert to bitmap
    m_bitmap = wxBitmap(img1);
    m_hoverBitmap = wxBitmap(img2);
    m_clickedBitmap = wxBitmap(img3);

    // Set initial bitmap
    m_bitmap = wxBitmap(m_bitmap.ConvertToImage().Scale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH));
    SetSize(size);

    Bind(wxEVT_PAINT, &Button::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &Button::OnMouseEvent, this);
    Bind(wxEVT_LEFT_UP, &Button::OnMouseEvent, this);
    Bind(wxEVT_LEAVE_WINDOW, &Button::OnMouseEvent, this);
    Bind(wxEVT_ENTER_WINDOW, &Button::OnMouseEvent, this);
}

void Button::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    if (m_clicked)
        dc.DrawBitmap(m_clickedBitmap, 0, 0);
    else if (m_hovered)
        dc.DrawBitmap(m_hoverBitmap, 0, 0);
    else
        dc.DrawBitmap(m_bitmap, 0, 0);
}

void Button::OnMouseEvent(wxMouseEvent& event) {
    if (event.LeftDown()) {
        m_clicked = true;
        Refresh();
    }
    else if (event.LeftUp() && m_clicked) {
        m_clicked = false;
        Refresh();
        wxCommandEvent evt(wxEVT_BUTTON, GetId());
        evt.SetEventObject(this);
        GetEventHandler()->ProcessEvent(evt);
    }
    else if (event.Leaving()) {
        m_hovered = false;
        m_clicked = false;
        Refresh();
    }
    else if (event.Entering()) {
        m_hovered = true;
        Refresh();
    }
}