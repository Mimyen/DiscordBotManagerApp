#include "MenuPopup.h"

MenuPopup::MenuPopup(wxWindow* parent, const wxSize& size, bool* open, std::vector<wxString> options, wxString* selectedOption, ButtonCallback callback, wxFont font)
    : m_size(size), isOpen(open)
{
    // Set background style to transparent
    SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);

    // Construct object
    Create(parent, wxTRANSPARENT);

    // Set up any additional initialization here
    SetSize(m_size.x, m_size.y * (options.size() < 3 ? options.size() : 3));

    scrollPanel = new ScrollPanel(
        this, 
        wxPoint(0, 0), 
        wxSize(m_size.x, m_size.y * (options.size() < 3 ? options.size() : 3)), 
        [this]() { 
            this->Dismiss(); 
            this->OnDismiss(); 
        }
    );

    for (auto& option : options) {
        scrollPanel->AddScrollControl<ScrollButton>(wxPoint(0, 0), wxSize(m_size.x, m_size.y), option, callback, font);
    }
}

void MenuPopup::OnPaint(wxPaintEvent& event)
{
    //
}

void MenuPopup::OnDismiss()
{
    // Perform any necessary cleanup here
    delete scrollPanel;
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