#pragma once
#include "ScrollControl.h"


class ScrollButton : public ScrollControl {
public:
    ScrollButton(wxWindow* parent, wxPoint pos, wxSize size, const wxString& label)
        : ScrollControl(parent, pos, size), m_label(label) {}

    void Draw(wxGraphicsContext* gc) override {
        wxGraphicsPath path = gc->CreatePath();
        path.AddRectangle(m_position.x * 2, m_position.y * 2, m_size.x * 2, m_size.y * 2); // Corner radius
        gc->SetBrush(wxBrush(m_isHovered ? hoverColour : defaultColour)); // Button color
        gc->FillPath(path);
        gc->SetFont(font, wxColour(255, 255, 255));
        wxDouble textWidth, textHeight, descent, externalLeading;
        gc->GetTextExtent(m_label, &textWidth, &textHeight, &descent, &externalLeading); // Measure text

        wxDouble xPos = m_position.x * 2 + (m_size.x * 2 - textWidth) / 2; // Center horizontally
        wxDouble yPos = m_position.y * 2 + (m_size.y * 2 - textHeight) / 2; // Center vertically

        gc->DrawText(m_label, xPos, yPos); // Draw centered text
    }

    void OnClick() override {
        // Handle button click action here
        wxMessageBox(m_label);
    }

private:
    wxString m_label;
    wxFont font = wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
};
