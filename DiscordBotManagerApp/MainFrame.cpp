#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), m_channelId(""), m_serverId("")
{
    try {
        socketHandler = new SocketHandler(BOT_IP, BOT_PORT);
    }
    catch (std::exception e) {
        wxMessageBox("Unable to connect to the server!");
        Close();
    }

    Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event) {});
    oldFrameSize = size;

    // Loading fonts
    light.AddPrivateFont("assets\\fonts\\gotham\\Light.ttf");
    medium.AddPrivateFont("assets\\fonts\\gotham\\Medium.ttf");
    bold.AddPrivateFont("assets\\fonts\\gotham\\Bold.ttf");

    // Set background color
    SetBackgroundColour(wxColour(0, 0, 0));
    SetSize(size);

    // Set title bar color
    SetTitleBarColor((HWND)GetHWND(), RGB(0, 0, 0));

    // Create login panel
    loginPanel = new wxPanel(this, wxID_ANY);
    SetupLoginPanel();

    // Main content
    mainPanel = new wxPanel(this, wxID_ANY);
    SetupMainPanel();

    // Main layout
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(loginPanel, 1, wxEXPAND | wxALL, 0); // Add the login panel with proportion 1
    mainSizer->Add(mainPanel, 1, wxEXPAND | wxALL, 0); // Add the main panel with proportion 1

    mainPanel->Hide();
    //loginPanel->Hide();

    SetSizerAndFit(mainSizer);
    //Centre();

    std::fstream loginData;
    loginData.open("loginData", std::ios::in | std::ios::out);

    std::string line;
    loginData >> line;

    if (line == "true") {
        loginData >> line;
        inputLogin->SetValue(line);

        loginData >> line;
        inputPassword->SetValue(line);

        leftPanelToggle->SetState(true);
    }
}

void MainFrame::SetTitleBarColor(HWND hwnd, DWORD color)
{
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, (const PVOID)DWMNCRP_DISABLED, sizeof(DWMNCRP_DISABLED));
    DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &color, sizeof(COLORREF));
}

void MainFrame::SetupLoginPanel()
{
    // Split the login panel into two halves
    rightPanel = new wxPanel(loginPanel, wxID_ANY);
    leftPanel = new RoundedPanel(loginPanel, wxID_ANY, 20, 5, 20, 20); // Use RoundedPanel instead of wxPanel

    // Setting up fonts
    wxFont tipFont = light;
    tipFont.SetPointSize(12);

    wxFont textFont = bold;
    textFont.SetPointSize(16);

    wxFont headerFont = bold;
    headerFont.SetPointSize(28);

    wxFont labelFont = light;
    labelFont.SetPointSize(12);

    // Left Panel
    leftPanelHeader = new Label(leftPanel, wxID_ANY, "Log in to Manager", wxPoint(25, 50), wxSize(600, 100), wxALIGN_CENTER_HORIZONTAL);
    leftPanelHeader->SetBackgroundColour(wxColour(18, 18, 18));
    leftPanelHeader->SetForegroundColour(wxColour(255, 255, 255));
    leftPanelHeader->SetFont(headerFont);

    button = new RoundedButton(
        leftPanel, 
        "Log In", 
        wxPoint(175, 380), 
        wxSize(300, 50),
        [this]() { 
            std::vector<std::string> data;
            data.push_back(this->inputLogin->GetValue().ToStdString());
            data.push_back(this->inputPassword->GetValue().ToStdString());
            std::vector<wxString> output = this->socketHandler->Handle(authorize, data);
            if (output[0] == "false") {
                wxMessageBox("Couldn't connect to the server!");
            }
            else {
                this->loginPanel->Hide();
                this->mainPanel->Show();
                this->Layout();

                std::fstream loginData;
                loginData.open("loginData", std::ios::out | std::ios::trunc);

                if (this->leftPanelToggle->GetState()) {
                    loginData << "true\n";
                    loginData << this->inputLogin->GetValue() << '\n';
                    loginData << this->inputPassword->GetValue();
                }
                else loginData << "false";
            }
        }
    );

    button->SetFont(tipFont);

    inputLogin = new LabeledTextInputPanel(
        leftPanel, 
        wxID_ANY, 
        "Username", 
        wxPoint(175, 190), 
        wxSize(300, 50), 
        wxTE_PROCESS_ENTER,
        [](wxString value) {

        },
        [this](wxString value) {
            inputPassword->SetFocus();
            inputPassword->m_textInput.SetInsertionPointEnd();
        }
    );

    inputLogin->SetFont(tipFont);
    inputLogin->SetLabelFont(labelFont);

    inputPassword = new LabeledTextInputPanel(
        leftPanel,
        wxID_ANY, 
        "Password", 
        wxPoint(175, 250), 
        wxSize(300, 50), 
        wxTE_PROCESS_ENTER,
        [](wxString value) {

        },
        [this](wxString value) {
            std::vector<std::string> data;
            data.push_back(this->inputLogin->GetValue().ToStdString());
            data.push_back(value.ToStdString());
            std::vector<wxString> output = this->socketHandler->Handle(authorize, data);
            if (output[0] == "false") {
                wxMessageBox("Couldn't connect to the server!");
            }
            else {
                this->loginPanel->Hide();
                this->mainPanel->Show();
                this->Layout();

                std::fstream loginData;
                loginData.open("loginData", std::ios::out | std::ios::trunc);

                if (this->leftPanelToggle->GetState()) {
                    loginData << "true\n";
                    loginData << this->inputLogin->GetValue() << '\n';
                    loginData << this->inputPassword->GetValue();
                }
                else loginData << "false";
            }
        }
    );

    inputPassword->SetEncrypted(true);
    inputPassword->SetFont(tipFont);
    inputPassword->SetLabelFont(labelFont);

    leftPanelToggle = new ToggleButton(
        leftPanel, 
        wxID_ANY, 
        wxPoint(175, 310), 
        wxSize(40, 20), 
        [this](bool flag = true) {

        }
    );

    leftPanelRMText = new Label(
        leftPanel, 
        wxID_ANY, 
        "Remember me", 
        wxPoint(220, 312), 
        wxSize(110, 18)
    );

    leftPanelRMText->SetFont(tipFont);
    leftPanelRMText->SetBackgroundColour(wxColour(18, 18, 18));
    leftPanelRMText->SetForegroundColour(wxColour(255, 255, 255));

    leftPanelLine1 = new RectangleObj(leftPanel, wxID_ANY, wxPoint(115, 150), wxSize(420, 1));
    leftPanelLine2 = new RectangleObj(leftPanel, wxID_ANY, wxPoint(115, 480), wxSize(420, 1));

    // Right Panel
    rightLabel = new Label(
        rightPanel, 
        wxID_ANY, 
        "Welcome to Mimyen Bot Manager", 
        wxPoint(160, 460), 
        wxSize(300, 20), 
        wxALIGN_CENTER_HORIZONTAL
    );

    rightLabel->SetForegroundColour(wxColour(255, 255, 255));
    rightLabel->SetFont(textFont);

    rightLowerLabel = new Label(
        rightPanel, 
        wxID_ANY, 
        "This application is designed to help\ndealing with the bot and it's behaviour.",
        wxPoint(160, 485), 
        wxSize(300, 200), 
        wxALIGN_CENTER_HORIZONTAL
    );

    rightLowerLabel->SetForegroundColour(wxColour(255, 255, 255));
    rightLowerLabel->SetFont(labelFont);

    rightLabelImage = new Image(rightPanel, wxID_ANY, wxPoint(160, 150), wxSize(300, 300));

    // Create a horizontal box sizer to contain the left and right panels
    wxBoxSizer* loginPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    loginPanelSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 0); // Add left panel with proportion 1 and 10px spacing
    loginPanelSizer->Add(rightPanel, 1, wxEXPAND | wxALL, 0); // Add right panel with proportion 1

    // Set the login panel's sizer
    loginPanel->SetSizer(loginPanelSizer);
}

void MainFrame::SetupMainPanel()
{
    wxFont hintFont = light;
    hintFont.SetPointSize(14);

    mainPanel->SetBackgroundColour(wxColour(0, 0, 0));

    mainPanelHome = new RoundedScrollPanel(
        mainPanel, 
        wxPoint(8, 0), 
        wxSize(64, 64)
    );

    mainPanelHome->AddControl<RoundedItem>(
        wxID_ANY, 
        wxDefaultPosition, 
        wxDefaultSize, 
        [this]() {
            mainPanelHome->UnselectAll();
            mainPanelFunctions->UnselectAll();
            HideMainPanelSubpanels();
            mainPanelHomeSubpanel->Show();
            return true;
        },
        "Home",
        true,
        "assets\\icon\\home.png",
        true,
        hintFont
    );
    

    mainPanelFunctions = new RoundedScrollPanel(
        mainPanel,
        wxPoint(8, 72),
        wxSize(64, 520)
    );

    mainPanelFunctions->AddControl<RoundedItem>(
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        [this]() {

            m_serverId = "";
            m_channelId = "";

            std::vector<wxString> output = this->socketHandler->Handle(getservers);

            if (output[0] == "true") {
                m_servers = std::vector<std::pair<wxString, wxString>>();

                for (size_t i = 1; i < output.size(); i += 2) {
                    m_servers.emplace_back(output[i], output[i + 1]);
                }
            }

            std::vector<wxString> items;

            for (auto& server : m_servers) {
                items.emplace_back(server.second);
            }

            delete messageSubpanelServers;
            delete messageSubpanelChannels;

            messageSubpanelServers = new DropdownMenu(
                mainPanelMessageSubpanel, 
                wxID_ANY, 
                wxPoint(50, 50), 
                wxSize(300, 50), 
                [this](wxString option) {
                    m_channelId = "";

                    for (auto& server : m_servers) {
                        if (server.second == option) {
                            m_serverId = server.first;

                            if (messageSubpanelChannels->GetItems().size() != 0) {
                                delete messageSubpanelChannels;

                                messageSubpanelChannels = new DropdownMenu(
                                    mainPanelMessageSubpanel,
                                    wxID_ANY,
                                    wxPoint(400, 50),
                                    wxSize(300, 50),
                                    [this](wxString option) {
                                        for (auto& channel : m_channels) {
                                            if (channel.second == option) {
                                                m_channelId = channel.first;
                                                break;
                                            }
                                        }
                                    },
                                    "Select Channel"
                                );
                            }

                            std::vector<std::string> data;

                            data.emplace_back(m_serverId.ToStdString());

                            std::vector<wxString> output = this->socketHandler->Handle(getchannels, data);

                            if (output[0] == "true") {
                                m_channels = std::vector<std::pair<wxString, wxString>>();

                                for (size_t i = 1; i < output.size(); i += 2) {
                                    m_channels.emplace_back(output[i], output[i + 1]);
                                }
                            }

                            std::vector<wxString> items;

                            for (auto& channel : m_channels) {
                                items.emplace_back(channel.second);
                            }

                            messageSubpanelChannels->SetItems(items);

                            break;
                        }
                    }

                    if (messageSubpanelChannels) messageSubpanelChannels->Resize(GetSize(), oldFrameSize);
                },
                "Select Server"
            );

            messageSubpanelChannels = new DropdownMenu(
                mainPanelMessageSubpanel,
                wxID_ANY,
                wxPoint(400, 50),
                wxSize(300, 50),
                [this](wxString option) {
                    for (auto& channel : m_channels) {
                        if (channel.second == option) {
                            m_channelId = channel.first;
                            // wxLogDebug(channel.first + " " + channel.second);
                            break;
                        }
                    }
                },
                "Select Channel"
            );

            if (messageSubpanelChannels) messageSubpanelChannels->Resize(GetSize(), oldFrameSize);
            if (messageSubpanelServers) messageSubpanelServers->Resize(GetSize(), oldFrameSize);

            messageSubpanelServers->SetItems(items);

            mainPanelHome->UnselectAll();
            mainPanelFunctions->UnselectAll();
            HideMainPanelSubpanels();
            mainPanelMessageSubpanel->Show();

            return true;
        },
        "Send Message",
        true,
        "assets\\icon\\message.png",
        false,
        hintFont
    );

    mainPanelLogout = new RoundedScrollPanel(
        mainPanel,
        wxPoint(8, 600),
        wxSize(64, 64)
    );
    mainPanelLogout->AddControl<RoundedItem>(
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        [this]() {
            mainPanelHome->SelectAll();
            mainPanelFunctions->UnselectAll();
            HideMainPanelSubpanels();
            mainPanelHomeSubpanel->Show();
            mainPanel->Hide();
            loginPanel->Show();
            Layout();

            return false;
        },
        "Log Out",
        true,
        "assets\\icon\\logout.png",
        false,
        hintFont
    );


    mainPanelHomeSubpanel = new RoundedPanel(mainPanel, wxID_ANY);
    mainPanelHomeSubpanel->SetRect(wxPoint(80, 0), wxSize(1192, 664));
    SetupHomeSubpanel();

    mainPanelMessageSubpanel = new RoundedPanel(mainPanel, wxID_ANY);
    mainPanelMessageSubpanel->SetRect(wxPoint(80, 0), wxSize(1192, 664));
    SetupMessageSubpanel();


    HideMainPanelSubpanels();
    mainPanelHomeSubpanel->Show();
}

void MainFrame::OnSize(wxSizeEvent& event)
{
    wxSize size = GetClientSize(); 

    button->Resize(size, oldFrameSize);
    inputPassword->Resize(size, oldFrameSize);
    inputLogin->Resize(size, oldFrameSize);
    rightLabel->Resize(size, oldFrameSize);
    rightLabelImage->Resize(size, oldFrameSize);
    rightLowerLabel->Resize(size, oldFrameSize);
    leftPanelLine1->Resize(size, oldFrameSize);
    leftPanelLine2->Resize(size, oldFrameSize);
    leftPanelHeader->Resize(size, oldFrameSize);
    leftPanelToggle->Resize(size, oldFrameSize);
    leftPanelRMText->Resize(size, oldFrameSize);
    mainPanelHome->Resize(size, oldFrameSize);
    mainPanelLogout->Resize(size, oldFrameSize);
    mainPanelFunctions->Resize(size, oldFrameSize);
    mainPanelHomeSubpanel->Resize(size, oldFrameSize);
    mainPanelMessageSubpanel->Resize(size, oldFrameSize);
    messageSubpanelInput->Resize(size, oldFrameSize);
    messageSubpanelAuthorName->Resize(size, oldFrameSize);
    messageSubpanelAuthorIcon->Resize(size, oldFrameSize);
    messageSubpanelSendButton->Resize(size, oldFrameSize);
    if (messageSubpanelChannels) messageSubpanelChannels->Resize(size, oldFrameSize);
    if (messageSubpanelServers) messageSubpanelServers->Resize(size, oldFrameSize);

    event.Skip();
}

void MainFrame::HideMainPanelSubpanels()
{
    mainPanelHomeSubpanel->Hide();
    mainPanelMessageSubpanel->Hide();
}

void MainFrame::SetupMessageSubpanel()
{
    wxFont labelFont = light;
    labelFont.SetPointSize(12);

    messageSubpanelInput = new LabeledTextInputPanel(
        mainPanelMessageSubpanel,
        wxID_ANY,
        "Message",
        wxPoint(50, 200),
        wxSize(300, 50),
        wxTE_PROCESS_ENTER
    );
    mainPanelMessageSubpanel->AddChildWidget(messageSubpanelInput);
    messageSubpanelInput->SetFont(labelFont);
    messageSubpanelInput->SetLabelFont(labelFont);

    messageSubpanelAuthorName = new LabeledTextInputPanel(
        mainPanelMessageSubpanel,
        wxID_ANY,
        "Author Name",
        wxPoint(50, 300),
        wxSize(300, 50),
        wxTE_PROCESS_ENTER
    );

    mainPanelMessageSubpanel->AddChildWidget(messageSubpanelAuthorName);
    messageSubpanelAuthorName->SetFont(labelFont);
    messageSubpanelAuthorName->SetLabelFont(labelFont);

    messageSubpanelAuthorIcon = new LabeledTextInputPanel(
        mainPanelMessageSubpanel,
        wxID_ANY,
        "Author Icon",
        wxPoint(400, 300),
        wxSize(300, 50),
        wxTE_PROCESS_ENTER,
        [this](wxString value) {
            wxLogDebug(value);
        },
        [this](wxString value) {
            wxLogDebug(value);
        }
    );

    mainPanelMessageSubpanel->AddChildWidget(messageSubpanelAuthorIcon);
    messageSubpanelAuthorIcon->SetFont(labelFont);
    messageSubpanelAuthorIcon->SetLabelFont(labelFont);

    messageSubpanelSendButton = new RoundedButton(
        mainPanelMessageSubpanel, 
        "Send Message", 
        wxPoint(400, 500), 
        wxSize(200, 50),
        [this]() {
            if (m_serverId != "" && m_channelId != "") {
                std::vector<std::string> data;

                data.emplace_back(m_serverId.ToStdString());
                data.emplace_back(m_channelId.ToStdString());
                data.emplace_back(messageSubpanelInput->GetValue());

                if (messageSubpanelEmbedToggle->GetState()) {
                    data.emplace_back("true");
                    data.emplace_back("0");
                    data.emplace_back("255");
                    data.emplace_back("255");
                }

                std::vector<wxString> output = this->socketHandler->Handle(sendmessage, data);

                if (output[0] == "false") {
                    wxLogDebug("Error");
                }
                else if (output[0] == wxString("true")) {
                    messageSubpanelInput->SetValue("");
                    messageSubpanelInput->Refresh();
                }
            }
        }
    );

    messageSubpanelEmbedToggle = new ToggleButton(
        mainPanelMessageSubpanel,
        wxID_ANY,
        wxPoint(50, 120),
        wxSize(40, 20),
        [this](bool flag = true) {
        
        }
    );
    messageSubpanelEmbedLabel = new Label(
        mainPanelMessageSubpanel,
        wxID_ANY,
        "Embed Format",
        wxPoint(95, 122),
        wxSize(110, 18)
    );

    messageSubpanelEmbedLabel->SetForegroundColour(wxColour(255, 255, 255));
    messageSubpanelEmbedLabel->SetBackgroundColour(wxColour(18, 18, 18));
    messageSubpanelEmbedLabel->SetFont(labelFont);
    
    wxFont titleFont = bold;
    titleFont.SetPointSize(24);

    messageSubpanelLabel = new Label(
        mainPanelMessageSubpanel,
        wxID_ANY,
        "Send Message Function",
        wxPoint(50, 10),
        wxSize(110, 50)
    );

    messageSubpanelLabel->SetForegroundColour(wxColour(255, 255, 255));
    messageSubpanelLabel->SetBackgroundColour(wxColour(18, 18, 18));
    messageSubpanelLabel->SetFont(titleFont);
}

void MainFrame::SetupHomeSubpanel()
{
    RoundedButton* button = new RoundedButton(mainPanelHomeSubpanel, "Pawel kox", wxPoint(50, 50), wxSize(200, 50), 
        [this]() { 
            for (auto& server : m_servers) {
                wxLogDebug(server.first + wxString(" ") + server.second);
            }
        }
    );
}



BEGIN_EVENT_TABLE(MainFrame, wxFrame)

END_EVENT_TABLE()