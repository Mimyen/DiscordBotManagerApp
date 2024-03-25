#include "ColorPickerPopup.h"

ColorPickerPopup::ColorPickerPopup(wxWindow* parent, unsigned int& r, unsigned int& g, 
    unsigned int& b, wxWindowID id, wxPoint pos, wxSize size, Callback onColorChange)
	: m_r(r), m_g(g), m_b(b), m_bInput(nullptr)
{
    SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
    Create(parent, id, "Color Picker", pos, size, wxNO_BORDER);

    m_rInput = new LabeledTextInputPanel(
        this,
        wxID_ANY,
        "Red",
        wxPoint(size.x - size.y / 20 - size.x / 5, size.y * 3 / 20),
        wxSize(size.x / 5, size.y * 3 / 20),
        wxTE_PROCESS_ENTER,
        [this](wxString value) {
            if (value == "") {
                m_r = 0;
                
                m_rInputLastValue = std::to_string(m_r).c_str();
                
                return;
            }

            if (value[0] == '0' && std::atoi(value.c_str()) > 0) {
                m_rInput->SetValue(value.SubString(1, value.size() - 1));
                m_rInput->m_textInput.SetInsertionPointEnd();
                return;
            }

            m_r = std::atoi(value.c_str());
            m_rInputLastValue = std::to_string(m_r).c_str();

            GetParent()->Refresh();
        },
        [this](wxString value) {
        
        },
        [this](wxString value) {
            bool correctInput = true;

            for (size_t i = 0; i < value.size(); i++) {
                if (!std::isdigit(value[i])) {
                    correctInput = false;
                    break;
                }
            }

            if (!correctInput) {
                m_rInput->SetValue(m_rInputLastValue);
                return false;

            }
            if (std::atoi(value.c_str()) > 255 || std::atoi(value.c_str()) < 0) {
                //long pointer = m_rInput->m_textInput.GetInsertionPoint();
                m_rInput->SetValue(m_rInputLastValue);
                //m_rInput->m_textInput.SetInsertionPoint(pointer - 1);
                return false;
            }

            return true;
        }
    );

    m_rInput->SetValue(std::to_string(m_r).c_str());
    m_rInput->Resize(wxSize(1, 1), wxSize(1, 1));
    m_rInput->SetBackgroundColour(wxColour(40, 40, 40));

    m_gInput = new LabeledTextInputPanel(
        this,
        wxID_ANY,
        "Green",
        wxPoint(size.x - size.y / 20 - size.x / 5, size.y * 7 / 20),
        wxSize(size.x / 5, size.y * 3 / 20),
        wxTE_PROCESS_ENTER,
        [this](wxString value) {
            if (value == "") {
                m_g = 0;

                m_gInputLastValue = std::to_string(m_g).c_str();

                return;
            }

            if (value[0] == '0' && std::atoi(value.c_str()) > 0) {
                m_gInput->SetValue(value.SubString(1, value.size() - 1));
                m_gInput->m_textInput.SetInsertionPointEnd();
                return;
            }

            m_g = std::atoi(value.c_str());
            m_gInputLastValue = std::to_string(m_g).c_str();

            GetParent()->Refresh();
        },
        [this](wxString value) {

        },
        [this](wxString value) {
            bool correctInput = true;

            for (size_t i = 0; i < value.size(); i++) {
                if (!std::isdigit(value[i])) {
                    correctInput = false;
                    break;
                }
            }

            if (!correctInput) {
                m_gInput->SetValue(m_gInputLastValue);
                return false;

            }
            if (std::atoi(value.c_str()) > 255 || std::atoi(value.c_str()) < 0) {
                //long pointer = m_rInput->m_textInput.GetInsertionPoint();
                m_gInput->SetValue(m_gInputLastValue);
                //m_rInput->m_textInput.SetInsertionPoint(pointer - 1);
                return false;
            }

            return true;
        }
    );

    m_gInput->SetValue(std::to_string(m_g).c_str());
    m_gInput->Resize(wxSize(1, 1), wxSize(1, 1));
    m_gInput->SetBackgroundColour(wxColour(40, 40, 40));

    m_bInput = new LabeledTextInputPanel(
        this,
        wxID_ANY,
        "Blue",
        wxPoint(size.x - size.y / 20 - size.x / 5, size.y * 11 / 20),
        wxSize(size.x / 5, size.y * 3 / 20),
        wxTE_PROCESS_ENTER,
        [this](wxString value) {
            if (value == "") {
                m_b = 0;

                m_bInputLastValue = std::to_string(m_b).c_str();

                return;
            }

            if (value[0] == '0' && std::atoi(value.c_str()) > 0) {
                m_bInput->SetValue(value.SubString(1, value.size() - 1));
                m_bInput->m_textInput.SetInsertionPointEnd();
                return;
            }

            m_b = std::atoi(value.c_str());
            m_bInputLastValue = std::to_string(m_b).c_str();

            GetParent()->Refresh();
        },
        [this](wxString value) {

        },
        [this](wxString value) {
            bool correctInput = true;

            for (size_t i = 0; i < value.size(); i++) {
                if (!std::isdigit(value[i])) {
                    correctInput = false;
                    break;
                }
            }

            if (!correctInput) {
                m_bInput->SetValue(m_bInputLastValue);
                return false;

            }
            if (std::atoi(value.c_str()) > 255 || std::atoi(value.c_str()) < 0) {
                //long pointer = m_rInput->m_textInput.GetInsertionPoint();
                m_bInput->SetValue(m_bInputLastValue);
                //m_rInput->m_textInput.SetInsertionPoint(pointer - 1);
                return false;
            }

            return true;
        }
    );

    m_bInput->SetValue(std::to_string(m_b).c_str());
    m_bInput->Resize(DUMMYRESIZE);
    m_bInput->SetBackgroundColour(wxColour(40, 40, 40));

    m_close = new SimpleRoundedButton(
        this, "x",
        wxPoint(size.x - size.y * 3 / 20, size.y * 3 / 80),
        wxSize(size.y / 10, size.y / 10), 
        [this]() {
            Hide();
        }
    );

    m_close->SetBackgroundColour(wxColour(40, 40, 40));
    m_close->SetForegroundColour(wxColour(255, 255, 255));
    m_close->SetColour(wxColour(18, 18, 18));
    m_close->SetPressedColour(wxColour(24, 24, 24));
    m_close->Resize(DUMMYRESIZE);
}

void ColorPickerPopup::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    Render(dc);
}

void ColorPickerPopup::Render(wxDC& dc)
{
    wxSize size = GetClientSize();

    // Create a bitmap with higher resolution for antialiasing
    wxBitmap bmp = Utils::CreateEmptyBitmap(size);
    wxMemoryDC memDC;
    memDC.SelectObject(bmp);

    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        // Draw the rounded rectangle on the bitmap
        gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

        gc->SetBrush(wxBrush(wxColour(60, 60, 60)));
        gc->DrawRoundedRectangle(0, 0, size.x * 2, size.y * 2, size.y / 8);

        gc->SetBrush(wxBrush(wxColour(40, 40, 40)));
        gc->DrawRoundedRectangle(3, 3, size.x * 2 - 6, size.y * 2 - 6, size.y / 8);

        delete gc;
    }

    // Scale down the bitmap to the original size for antialiasing effect
    wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}

void ColorPickerPopup::OnClose(wxCloseEvent& event)
{
    event.Skip();
}

wxBEGIN_EVENT_TABLE(ColorPickerPopup, wxDialog)
    EVT_PAINT(ColorPickerPopup::OnPaint)
    EVT_CLOSE(ColorPickerPopup::OnClose)
wxEND_EVENT_TABLE()