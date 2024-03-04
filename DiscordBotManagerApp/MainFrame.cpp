#include "MainFrame.h"



void OnButtonClick(MainFrame* master)
{
    master->loginPanel->Hide();
    master->mainPanel->Show();
    master->Layout();
}

void bOnButtonClick(bool flag) {
    // Perform some action when the button is clicked
    // For example, display a message box
    // wxMessageBox("Button clicked!");

    wxLogDebug(std::to_string(flag).c_str());
}


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
    oldFrameSize = GetClientSize();

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
    leftPanel = new RoundedPanel(loginPanel, wxID_ANY, wxColour(18, 18, 18), wxColour(0 ,0, 0), 10, 0, 10, 10); // Use RoundedPanel instead of wxPanel

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
    leftPanelHeader = new Label(leftPanel, wxID_ANY, "Log in to Manager", wxPoint(10, 50), wxSize(600, 100), wxALIGN_CENTER_HORIZONTAL);
    leftPanelHeader->SetBackgroundColour(wxColour(18, 18, 18));
    leftPanelHeader->SetForegroundColour(wxColour(255, 255, 255));
    leftPanelHeader->SetFont(headerFont);

    button = new RoundedButton(leftPanel, "Log In", wxPoint(160, 380), wxSize(300, 50),
        wxColour(26, 188, 156), wxColour(17, 120, 99), wxColour(18, 18, 18), wxColour(0, 0, 0), [this]() { OnButtonClick(this); });
    button->SetFont(tipFont);

    inputLogin = new LabeledTextInputPanel(leftPanel, wxID_ANY, "Username", wxPoint(160, 190), wxSize(300, 50), wxTE_PROCESS_ENTER, wxDefaultValidator, "name", button);
    inputLogin->SetFont(tipFont);
    inputLogin->SetLabelFont(labelFont);

    inputPassword = new LabeledTextInputPanel(leftPanel, wxID_ANY, "Password", wxPoint(160, 250), wxSize(300, 50), wxTE_PROCESS_ENTER, wxDefaultValidator, "name", button);
    inputPassword->SetEncrypted(true);
    inputPassword->SetFont(tipFont);
    inputPassword->SetLabelFont(labelFont);

    leftPanelToggle = new ToggleButton(leftPanel, wxID_ANY, wxPoint(160, 310), wxSize(40, 20), bOnButtonClick);

    leftPanelRMText = new Label(leftPanel, wxID_ANY, "Remember me", wxPoint(205, 312), wxSize(110, 18));
    leftPanelRMText->SetFont(tipFont);
    leftPanelRMText->SetBackgroundColour(wxColour(18, 18, 18));
    leftPanelRMText->SetForegroundColour(wxColour(255, 255, 255));

    leftPanelLine1 = new RectangleObj(leftPanel, wxID_ANY, wxPoint(100, 150), wxSize(420, 1));
    leftPanelLine2 = new RectangleObj(leftPanel, wxID_ANY, wxPoint(100, 480), wxSize(420, 1));

    // Right Panel
    rightLabel = new Label(rightPanel, wxID_ANY, "Welcome to Mimyen Bot Manager", wxPoint(160, 460), wxSize(300, 20), wxALIGN_CENTER_HORIZONTAL);
    rightLabel->SetForegroundColour(wxColour(255, 255, 255));
    rightLabel->SetFont(textFont);

    rightLowerLabel = new Label(rightPanel, wxID_ANY, "This application is designed to help\ndealing with the bot and it's behaviour.",
        wxPoint(160, 485), wxSize(300, 200), wxALIGN_CENTER_HORIZONTAL);
    rightLowerLabel->SetForegroundColour(wxColour(255, 255, 255));
    rightLowerLabel->SetFont(labelFont);

    rightLabelImage = new Image(rightPanel, wxID_ANY, wxPoint(160, 150), wxSize(300, 300));

    // Create a horizontal box sizer to contain the left and right panels
    wxBoxSizer* loginPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    loginPanelSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 10); // Add left panel with proportion 1 and 10px spacing
    loginPanelSizer->Add(rightPanel, 1, wxEXPAND | wxALL, 0); // Add right panel with proportion 1

    // Set the login panel's sizer
    loginPanel->SetSizer(loginPanelSizer);
}

void MainFrame::SetupMainPanel()
{
    mainPanel->SetBackgroundColour(wxColour(0, 0, 0));
    
    RoundedPanel* panel = new RoundedPanel(mainPanel, wxID_ANY, wxColour(18, 18, 18), wxColour(0, 0, 0), 0, 0, 0, 0);
    wxBoxSizer* mainPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    mainPanelSizer->Add(panel, 1, wxEXPAND | wxALL, 0);
    menu = new DropdownMenu(panel, wxID_ANY, wxPoint(50, 50), wxSize(200, 50));
    menu->AddItem("Item 1");
    menu->AddItem("Item 2");
    menu->AddItem("Item 3");
    menu->AddItem("Item 4");
    menu->AddItem("Item 5");


    mainPanel->SetSizer(mainPanelSizer);
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
    menu->Resize(size, oldFrameSize);
    //wxLogDebug(std::to_string(rightPanel->GetSize().GetWidth()).c_str());
    //wxLogDebug(std::to_string(rightPanel->GetSize().GetHeight()).c_str());
    event.Skip();
}



BEGIN_EVENT_TABLE(MainFrame, wxFrame)

END_EVENT_TABLE()