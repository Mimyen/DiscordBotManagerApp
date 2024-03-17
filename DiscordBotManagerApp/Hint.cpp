#include "Hint.h"

Hint::Hint(wxWindow* parent, wxString label)
    : m_label(label)
{
	SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
	Create(parent, wxTRANSPARENT);
}

void Hint::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	Render(dc);
}

void Hint::Render(wxDC& dc)
{
    wxSize size = GetClientSize();
    
    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp = Utils::CreateEmptyBitmap(size);
    wxMemoryDC memDC;
    memDC.SelectObject(bmp);

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        // Draw the rounded rectangle on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

        gc->SetBrush(wxBrush(wxColour(40, 40, 40)));
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, 10);

        wxFont font = GetFont();
        font.SetPointSize(font.GetPointSize() * 2);
        gc->SetFont(font, wxColour(255, 255, 255));
        wxDouble textWidth, textHeight, descent, externalLeading;
        gc->GetTextExtent(m_label, &textWidth, &textHeight, &descent, &externalLeading); // Measure text

        wxDouble xPos = (size.x * 2 - textWidth) / 2; // Center horizontally
        wxDouble yPos = (size.y * 2 - textHeight) / 2; // Center vertically

        gc->DrawText(m_label, xPos, yPos); // Draw centered text
        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

BEGIN_EVENT_TABLE(Hint, wxPopupTransientWindow)
    EVT_PAINT(Hint::OnPaint)
END_EVENT_TABLE()