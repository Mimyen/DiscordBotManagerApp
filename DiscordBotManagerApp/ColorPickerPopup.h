#pragma once

#include "LabeledTextInputPanel.h"
#include "SimpleRoundedButton.h"

class ColorPickerPopup : public wxDialog
{
public:
	using Callback = std::function<void(unsigned int r, unsigned int g, unsigned int b)>;
	ColorPickerPopup(wxWindow* parent, unsigned int& r, unsigned int& g, unsigned int& b, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, Callback onColorChange = [](unsigned int r, unsigned int g, unsigned int b) {});

private:
	/// <summary>
	/// Repaints the window.
	/// </summary>
	/// <param name="event">wxPaintEvent that happens whenever element is refreshed.</param>
	virtual void OnPaint(wxPaintEvent& event);

	/// <summary>
	/// Inner function that draws the elemsent.
	/// </summary>
	/// <param name="dc">Drawing component from wxWidgets.</param>
	virtual void Render(wxDC& dc);

	virtual void OnClose(wxCloseEvent& event);

	unsigned int& m_r;
	unsigned int& m_g;
	unsigned int& m_b;

	LabeledTextInputPanel* m_rInput;
	wxString m_rInputLastValue;
	LabeledTextInputPanel* m_gInput;
	wxString m_gInputLastValue;
	LabeledTextInputPanel* m_bInput;
	wxString m_bInputLastValue;
	SimpleRoundedButton* m_close;
	SimpleRoundedButton* m_ok;
	Callback m_callback;

	DECLARE_EVENT_TABLE()
};

