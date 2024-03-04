#include "DiscordBotManagerApp.h"

wxIMPLEMENT_APP(DiscordBotManagerApp);

bool DiscordBotManagerApp::OnInit()
{
    // Make program not be scaled with desktop scaling (so it won't be blurry)
    SetProcessDPIAware();

    // Create the window
    MainFrame* frame = new MainFrame(TITLE, GetCenter(), SIZE);

    // Set the window icon
    wxInitAllImageHandlers();
    wxIcon Icon;
    Icon.LoadFile(wxT("assets\\icon\\icon.png"), wxBITMAP_TYPE_PNG, 2);

    // Set Icon for the program
    frame->SetIcon(Icon);

    // Set the initial size of the window
    frame->SetSizeHints(SIZE);
    frame->SetClientSize(SIZE);
    frame->Show(true);

    return true;
}

wxPoint DiscordBotManagerApp::GetCenter()
{
    // Get screen size
    wxSize screenSize = wxGetDisplaySize();

    // Calculate position of the window
    int xPos = (screenSize.GetWidth() / 2 - SIZE.GetX() / 2);
    int yPos = (screenSize.GetHeight() / 2 - SIZE.GetY() / 2);

    return wxPoint(xPos, yPos);
}

