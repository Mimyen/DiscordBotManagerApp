#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    try {
        socketHandler = new SocketHandler(BOT_IP, BOT_PORT);
    }
    catch (std::exception e) {
        wxMessageBox("Unable to connect to the server!");
        Close();
    }

    Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
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

            if (this->socketHandler->Handle(authorize, data) == "false") {
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
        wxDefaultValidator, 
        "name", 
        button
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
        wxDefaultValidator, 
        "name", 
        button
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

    event.Skip();
}

void MainFrame::HideMainPanelSubpanels()
{
    mainPanelHomeSubpanel->Hide();
    mainPanelMessageSubpanel->Hide();
}

void MainFrame::SetupMessageSubpanel()
{
    RoundedButton* button = new RoundedButton(mainPanelMessageSubpanel, "Pawel kox", wxPoint(50, 50), wxSize(200, 50), []() { wxLogDebug("Pawel kox"); });
}

void MainFrame::SetupHomeSubpanel()
{
    RoundedButton* button = new RoundedButton(mainPanelHomeSubpanel, "Pawel cw3l", wxPoint(50, 50), wxSize(200, 50), []() { wxLogDebug("Pawel kox"); });
}



BEGIN_EVENT_TABLE(MainFrame, wxFrame)

END_EVENT_TABLE()