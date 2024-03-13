#include "MenuPopup.h"

MenuPopup::MenuPopup(wxWindow* parent, const wxSize& size, bool* open, std::vector<wxString> options, wxString* selectedOption, ButtonCallback callback)
    : m_size(size), isOpen(open)
{
    // Set background style to transparent
    SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);

    // Construct object
    Create(parent, wxTRANSPARENT);

    // Set up any additional initialization here
    SetSize(m_size.x, m_size.y * (options.size() < 3 ? options.size() : 3));

    ScrollPanel* scrollPanel = new ScrollPanel(
        this, 
        wxPoint(0, 0), 
        wxSize(m_size.x, m_size.y * (options.size() < 3 ? options.size() : 3)), 
        [this]() { 
            this->Dismiss(); 
            this->OnDismiss(); 
        }
    );

    for (auto& option : options) {
        scrollPanel->AddScrollControl<ScrollButton>(wxPoint(0, 0), wxSize(m_size.x, m_size.y), option, callback);
    }
}

void MenuPopup::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // Create a memory DC with the same properties as the paint DC
    wxMemoryDC memDC(&dc);

    // Get size of the element
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp = Utils::CreateEmptyBitmap(size);

    // Select the bitmap into the memory DC
    memDC.SelectObject(bmp);

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        // Set blending mode for transparency
        gc->SetCompositionMode(wxCOMPOSITION_OVER);

        // Draw the rounded rectangle outline on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
        gc->SetBrush(wxBrush(wxColour(114, 114, 114, 255))); // Set alpha to 255 (opaque)
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, m_size.y / 4);

        delete gc;
    }

    // Rescale bitmap for better quality
    bmp.Rescale(bmp, size);

    // Draw the bitmap on the device context
    dc.DrawBitmap(bmp, 0, 0, true);
}

void MenuPopup::OnDismiss()
{
    // Perform any necessary cleanup here
    Close();

    if (isOpen && !wxRect(GetParent()->GetScreenPosition(), GetParent()->GetSize()).Contains(wxGetMousePosition())) *isOpen = false;
    GetParent()->Refresh();
}

void MenuPopup::OnMouseEvents(wxMouseEvent& event)
{
    event.Skip();
}

wxBEGIN_EVENT_TABLE(MenuPopup, wxPopupTransientWindow)
    EVT_PAINT(MenuPopup::OnPaint)
    EVT_LEFT_DOWN(MenuPopup::OnMouseEvents)
    EVT_RIGHT_DOWN(MenuPopup::OnMouseEvents)
wxEND_EVENT_TABLE()