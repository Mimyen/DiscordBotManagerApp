#include "DropdownMenu.h"

DropdownMenu::DropdownMenu(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, FunctionCallback callback, wxString defaultLabel, wxFont font)
	: wxPanel(parent, id, pos, size, wxTRANSPARENT_WINDOW), m_isMenuVisible(false),
    defaultPos(pos), defaultSize(size), isOpen(false), selectedOption(""), m_callback(callback), m_defaultLabel(defaultLabel), defaultFontSize(font.GetPointSize())
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(wxColour(18, 18, 18, 0));
    SetFont(font);

    Bind(wxEVT_PAINT, &DropdownMenu::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DropdownMenu::OnMouseLeftDown, this);
}

void DropdownMenu::AddItem(const wxString& item)
{
	m_items.push_back(item);
}

void DropdownMenu::SetItems(const std::vector<wxString>& items)
{
    m_items = items;
    Refresh();
}

std::vector<wxString> DropdownMenu::GetItems() const
{
    return m_items;
}

void DropdownMenu::Select(const wxString& item)
{
    for (auto& m_item : m_items) {
        if (m_item == item) {
            selectedOption = item;
            Refresh();
        }
    }
}

void DropdownMenu::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int menuX = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int menuY = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int menuWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int menuHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

    wxFont buffer = GetFont();
    double b = (double)windowSize.y / (double)defaultWindowSize.y * (double)defaultFontSize;
    buffer.SetPointSize(b);
    SetFont(buffer);

    // Set the new position and size for the menu
    SetSize(menuWidth, menuHeight, menuX, menuY);
}

void DropdownMenu::Render(wxDC& dc)
{
    dc.Clear();
    //dc.SetDeviceOrigin(GetPosition().x, GetPosition().y);
    // Get size of the element
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp = Utils::CreateEmptyBitmap(size); 

    // Initialize object responsible for storing what is drawn in the memory
    wxMemoryDC memDC(&dc);
    memDC.Clear();
    memDC.SelectObject(bmp);


    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
    
        // Set blending mode for transparency
        gc->SetCompositionMode(wxCOMPOSITION_OVER);

        // Draw the rounded rectangle outline on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
        
        gc->SetBrush(wxBrush(wxColour(60, 60, 60, 255))); // Set alpha to 255 (opaque)
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, size.y / 4);
        gc->SetFont(Utils::UpscaledFont(GetFont()), wxColour(255, 255, 255));
        wxDouble textWidth, textHeight, descent, externalLeading;
        gc->GetTextExtent(selectedOption.size() > 0 ? selectedOption : m_defaultLabel, &textWidth, &textHeight, &descent, &externalLeading); // Measure text

        wxDouble xPos = (size.x * 2 - textWidth) / 2; // Center horizontally
        wxDouble yPos = (size.y * 2 - textHeight) / 2; // Center vertically

        gc->DrawText(selectedOption.size() > 0 ? selectedOption : m_defaultLabel, xPos, yPos); // Draw centered text

        gc->GetTextExtent(this->isOpen ? wxString("-") : wxString("+"), &textWidth, &textHeight, &descent, &externalLeading); // Measure text

        xPos = size.x * 2 - (size.y * 2 - textHeight) / 2; // Center horizontally
        yPos = (size.y * 2 - textHeight) / 2; // Center vertically

        gc->DrawText(this->isOpen ? wxString("-") : wxString("+"), xPos, yPos); // Draw centered text


        delete gc;
    }

    // Rescale bitmap for better quality
    bmp.Rescale(bmp, size); // Rescale to original size

    // Draw the bitmap on the device context
    dc.DrawBitmap(bmp, 0, 0, true);
}

void DropdownMenu::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    Render(dc);
}

void DropdownMenu::OnMouseLeftDown(wxMouseEvent& event)
{
    if (!isOpen) {
        // Create and display the custom popup window
        MenuPopup* popup = new MenuPopup(
            this,
            GetSize(),
            &isOpen,
            m_items,
            &selectedOption,
            [this](wxString item) {
                this->Select(item);
                if (this->m_callback)
                    this->m_callback(this->selectedOption);
            },
            GetFont()
        );

        // Position the popup below the menu
        popup->SetPosition(GetScreenPosition() + wxPoint(0, GetSize().y + 5));

        // Display the popup window
        popup->Popup();

        isOpen = true;
        Refresh();
    }
    else isOpen = false;
    
}