#pragma once

#include "Utils.h"

class WebView
{
public:

	WebView(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, wxString address = "https://www.google.com");

    /// <summary>
    /// Resizes the window in relation to window size.
    /// </summary>
    /// <param name="windowSize">Current window size.</param>
    /// <param name="defaultWindowSize">Size of the window that it is created with.</param>
    virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

    wxWebView* webView;
private:
    virtual void OnWebsiteLoad(wxWebViewEvent& event);

	wxSize defaultSize;
	wxPoint defaultPos;
};

