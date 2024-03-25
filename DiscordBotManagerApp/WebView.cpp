#include "WebView.h"

WebView::WebView(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, wxString address)
	: defaultSize(size), defaultPos(pos)
{
    webView = wxWebView::New(parent, wxID_ANY, wxString::FromAscii(wxWebViewDefaultURLStr), wxPoint(), wxSize(), wxWebViewBackendEdge);
    webView->SetSize(wxRect(pos, size));
    webView->LoadURL(address);
}

void WebView::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int objectX = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int objectY = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int objectWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int objectHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the object
    webView->SetSize(objectWidth, objectHeight, objectX, objectY);
}

void WebView::OnWebsiteLoad(wxWebViewEvent& event)
{
   
}
