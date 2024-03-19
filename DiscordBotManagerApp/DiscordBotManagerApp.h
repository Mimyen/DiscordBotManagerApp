#pragma once

#include "libs.h"
#include "MainFrame.h"

#define TITLE "Mimyen Bot Manager Application"
#define SIZE wxSize(1280, 672)

/// <summary>
/// This class initializes the window.
/// </summary>
class DiscordBotManagerApp : public wxApp {
public:
    /// <summary>
    /// Function that initializes the window.
    /// </summary>
    virtual bool OnInit();

    /// <summary>
    /// Function that calculates where the window will appear so that it will look centered.
    /// </summary>
    /// <returns>Position in which window will appear</returns>
    wxPoint GetCenter();
};

