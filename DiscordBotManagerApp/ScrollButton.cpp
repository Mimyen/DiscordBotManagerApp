#include "ScrollButton.h"

void ScrollButton::Draw(wxGraphicsContext* gc)
{
    wxGraphicsPath path = gc->CreatePath();
    path.AddRectangle(m_position.x * 2, m_position.y * 2, m_size.x * 2, m_size.y * 2); // Corner radius
    gc->SetBrush(wxBrush(m_isHovered ? hoverColour : defaultColour)); // Button color
    gc->FillPath(path);
    gc->SetFont(Utils::UpscaledFont(font), wxColour(255, 255, 255));
    wxDouble textWidth, textHeight, descent, externalLeading;
    gc->GetTextExtent(m_label, &textWidth, &textHeight, &descent, &externalLeading); // Measure text

    wxDouble xPos = m_position.x * 2 + (m_size.x * 2 - textWidth) / 2; // Center horizontally
    wxDouble yPos = m_position.y * 2 + (m_size.y * 2 - textHeight) / 2; // Center vertically

    gc->DrawText(m_label, xPos, yPos); // Draw centered text
}

void ScrollButton::OnClick()
{
    if (callback) {
        callback(m_label);
    }
}
