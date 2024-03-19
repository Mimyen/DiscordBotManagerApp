#pragma once

#include "libs.h"
#include "SocketHandler.h"
#include "RoundedPanel.h"
#include "RoundedButton.h"
#include "TextInputPanel.h"
#include "LabeledTextInputPanel.h"
#include "Label.h"
#include "RectangleObj.h"
#include "Image.h"
#include "ToggleButton.h"
#include "DropdownMenu.h"
#include "Slider.h"
#include "RoundedScrollPanel.h"

#define BOT_IP L"127.0.0.1"
#define BOT_PORT 2222

/// <summary>
/// This class represents entire frame of the main window.
/// </summary>
class MainFrame : public wxFrame {
public:
    /// <summary>
    /// Contructor for MainFrame class.
    /// </summary>
    /// <param name="title">Title of the window that will be created.</param>
    /// <param name="pos">Position where Image will be drawn.</param>
    /// <param name="size">Size of the Image.</param>
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    /// <summary>
    /// Setter for title bar color.
    /// </summary>
    /// <param name="hwnd">Handle to the window.</param>
    /// <param name="color">Color that will be set to title bar.</param>
    void SetTitleBarColor(HWND hwnd, DWORD color);

    /// <summary>
    /// Sets up LoginPanel.
    /// </summary>
    void SetupLoginPanel();

    /// <summary>
    /// Sets up MainPanel.
    /// </summary>
    void SetupMainPanel();

    /// <summary>
    /// Function that is called whenever window changes it's size.
    /// </summary>
    /// <param name="event">Event that is called.</param>
    void OnSize(wxSizeEvent& event);

    void HideMainPanelSubpanels();

    void SetupMessageSubpanel();

    void SetupHomeSubpanel();

    wxFont light = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
    wxFont medium = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);
    wxFont bold = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);


public:
    wxSize oldFrameSize;
    SocketHandler* socketHandler;

    // Main panels
    wxPanel* loginPanel;
    wxPanel* mainPanel;

    wxBoxSizer* mainSizer;

    // loginPanel -> rightPanel
    wxPanel* rightPanel;
    Label* rightLabel;
    Label* rightLowerLabel;
    Image* rightLabelImage;

    // loginPanel -> leftPanel
    RoundedPanel* leftPanel;
    Label* leftPanelHeader;
    RoundedButton* button;
    LabeledTextInputPanel* inputLogin;
    LabeledTextInputPanel* inputPassword;
    RectangleObj* leftPanelLine1;
    RectangleObj* leftPanelLine2;
    ToggleButton* leftPanelToggle;
    Label* leftPanelRMText;

    // mainPanel
    RoundedScrollPanel* mainPanelHome;
    RoundedScrollPanel* mainPanelLogout;
    RoundedScrollPanel* mainPanelFunctions;
    RoundedPanel* mainPanelHomeSubpanel;
    RoundedPanel* mainPanelMessageSubpanel;

    // mainPanel->HomeSubpanel


    // mainPanel->MessageSubpanel
    std::vector<std::pair<wxString, wxString>> m_servers;
    std::vector<std::pair<wxString, wxString>> m_channels;
    wxString m_serverId;
    wxString m_channelId;
    DropdownMenu* messageSubpanelServers;
    DropdownMenu* messageSubpanelChannels;
    RoundedButton* messageSubpanelSendButton;
    LabeledTextInputPanel* messageSubpanelInput;
    LabeledTextInputPanel* messageSubpanelAuthorName;
    LabeledTextInputPanel* messageSubpanelAuthorIcon;
    ToggleButton* messageSubpanelEmbedToggle;
    Label* messageSubpanelEmbedLabel;
    Label* messageSubpanelLabel;

    DECLARE_EVENT_TABLE();
};
