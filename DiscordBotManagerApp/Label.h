#pragma once

#include "libs.h"

/// <summary>
/// This class creates a label.
/// </summary>
class Label : public wxStaticText
{
public:
	/// <summary>
	/// Constructor for Label class.
	/// </summary>
	/// <param name="parent">Pointer to cointainer that component will be in.</param>
	/// <param name="id">Id of the object, useable for making calls.</param>
	/// <param name="text">Text displayed.</param>
	/// <param name="pos">Position where component will be drawn.</param>
	/// <param name="size">Size of the component.</param>
	/// <param name="style">Style for the input.</param>
	/// <param name="name">Name of the component.</param>
	Label(wxWindow* parent, wxWindowID id, const wxString& text, const wxPoint& position = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0L, const wxString& name = wxString::FromAscii(wxStaticTextNameStr));
	
	/// <summary>
	/// Resizes the window in relation to window size.
	/// </summary>
	/// <param name="windowSize">Current window size.</param>
	/// <param name="defaultWindowSize">Size of the window that it is created with.</param>
	virtual void Resize(wxSize windowSize, wxSize defaultWindowSize);
	
	/// <summary>
	/// Setter function for the font.
	/// </summary>
	/// <param name="font">Font that will be set.</param>
	virtual void SetFont(wxFont font);

protected:
	int fontDefaultSize;
	wxSize defaultSize;
	wxPoint defaultPos;
};

