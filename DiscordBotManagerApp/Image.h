#pragma once
#include "libs.h"


/// <summary>
/// This class draws an image from png.
/// </summary>
class Image : public wxPanel
{
public:
	/// <summary>
	/// Contructor for Image class.
	/// </summary>
	/// <param name="parent">Pointer to cointainer that Image class will be in.</param>
	/// <param name="id">Id of the object, useable for making calls.</param>
	/// <param name="pos">Position where Image will be drawn.</param>
	/// <param name="size">Size of the Image.</param>
	/// <param name="path">Path to file that contains the image in png format.</param>
	Image(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, wxString path = "assets\\icon\\icon.png");
	
	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);

protected:
	/// <summary>
	/// Repaints the window.
	/// </summary>
	/// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
	/// <returns></returns>
	virtual void OnPaint(wxPaintEvent& event);

	/// <summary>
	/// Inner function that draws the element.
	/// </summary>
	/// <param name="dc">Drawing component from wxWidgets.</param>
	virtual void Render(wxDC& dc);

	wxPoint defaultPos;
	wxSize defaultSize;

	wxImage image;
};

