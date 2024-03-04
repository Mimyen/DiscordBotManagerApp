#include "Label.h"

Label::Label(wxWindow* parent, wxWindowID id, const wxString& text, const wxPoint& position, const wxSize& size, long style, const wxString& name)
	: wxStaticText(parent, id, text, position, size, style, name)
{
	defaultSize = size;
	defaultPos = position;
	fontDefaultSize = GetFont().GetPointSize();
}

void Label::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int labelWidth = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int labelHeight = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int labelX = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int labelY = defaultPos.y * windowSize.y / defaultWindowSize.y;
    int fontSize = fontDefaultSize * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the label
    SetSize(labelX, labelY, labelWidth, labelHeight);
    
    wxFont buffer = GetFont();
    buffer.SetPointSize(fontSize);
    wxStaticText::SetFont(buffer);

    // Check if wxALIGN_CENTER_HORIZONTAL flag is set
    if (GetWindowStyle() & wxALIGN_CENTER_HORIZONTAL) {
        // Get the text extent to determine its width
        int textWidth, textHeight;
        GetTextExtent(GetLabel(), &textWidth, &textHeight);

        // Calculate the horizontal offset to center the text
        int offsetX = (labelWidth - textWidth) / 2;

        // Calculate the vertical offset to center the text vertically
        int offsetY = (labelHeight - textHeight) / 2;

        // Adjust the label's position to center the text
        SetSize(labelX + offsetX, labelY, textWidth, labelHeight);
    }

    Refresh();
}

void Label::SetFont(wxFont font)
{
	wxStaticText::SetFont(font);
	fontDefaultSize = font.GetPointSize();
}
