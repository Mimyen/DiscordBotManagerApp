#pragma once

#include <wx/wx.h>

class Button : public wxControl 
{
public:
    Button(wxWindow* parent, const wxString& imageName, const wxString& hoverImageName, const wxString& clickedImageName,
        const wxPoint& pos, const wxSize& size, unsigned int id);

private:
    wxString m_imageName;
    wxString m_hoverImageName;
    wxString m_clickedImageName;
    bool m_hovered;
    bool m_clicked;

    wxBitmap m_bitmap;
    wxBitmap m_hoverBitmap;
    wxBitmap m_clickedBitmap;

    void OnPaint(wxPaintEvent& event);
    void OnMouseEvent(wxMouseEvent& event);
};

