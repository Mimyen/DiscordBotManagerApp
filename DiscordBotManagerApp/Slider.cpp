#include "Slider.h"

Slider::Slider(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, FunctionCallback callback)
	: defaultPos(pos), defaultSize(size), bg(wxColour(18, 18, 18)), fg(wxColour(255, 255, 255)), hover(wxColour(26, 188, 156)),
	bar(wxColour(60, 60, 60)), m_callback(callback), m_value(0.5), wxPanel(parent, id, pos, size), m_isHovered(false), m_isDragging(false)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void Slider::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
	// Calculate new size of the element
	int objectX = defaultSize.x * windowSize.x / defaultWindowSize.x;
	int objectY = defaultSize.y * windowSize.y / defaultWindowSize.y;
	int objectWidth = defaultPos.x * windowSize.x / defaultWindowSize.x;
	int objectHeight = defaultPos.y * windowSize.y / defaultWindowSize.y;

	// Set the new position and size for the object
	SetSize(objectWidth, objectHeight, objectX, objectY);

	Refresh();
}

bool Slider::SetBackgroundColour(const wxColour& colour)
{
	try {
		bg = colour;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

bool Slider::SetBarColour(const wxColour& colour)
{
	try {
		bar = colour;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

bool Slider::SetHoverColour(const wxColour& colour)
{
	try {
		hover = colour;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

bool Slider::SetForegroundColour(const wxColour& colour)
{
	try {
		fg = colour;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

void Slider::SetValue(const double& value)
{
}

double Slider::GetValue() const
{
	return m_value;
}

void Slider::Render(wxDC& dc)
{
	wxSize size = GetClientSize();

	// Create a bitmap with higher resolution for antialiasing
	wxBitmap bmp(size * 2);
	wxMemoryDC memDC;
	memDC.SelectObject(bmp);

	// Set the background color
	memDC.SetBackground(wxBrush(bg));
	memDC.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
	if (gc) {
		// Draw the rounded rectangle on the bitmap
		gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

		// Draw rounded rectangle
		gc->SetBrush(wxBrush(bar));
		gc->DrawRoundedRectangle(
			size.y / 2, 
			size.y - size.y / 2, 
			size.x * 2 - size.y, 
			size.y, 
			size.y / 2
		);

		if (m_value > 0) {
			gc->SetBrush(wxBrush(m_isHovered || m_isDragging ? hover : fg));
			gc->DrawRoundedRectangle(
				size.y / 2, 
				size.y - size.y / 2, 
				m_value * (size.x * 2 - size.y), 
				size.y, 
				size.y / 2
			);
		}

		if (m_isHovered || m_isDragging) {
			gc->SetBrush(wxBrush(fg));
			gc->DrawRoundedRectangle(m_value * (size.x * 2 - size.y * 2), 0, size.y * 2, size.y * 2, size.y);
		}
	}

	// Scale down the bitmap to the original size for antialiasing effect
	wxImage img = bmp.ConvertToImage().Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);
	wxBitmap finalBmp(img);

	// Draw the bitmap on the device context
	dc.DrawBitmap(finalBmp, 0, 0, true);
}

void Slider::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	Render(dc);
}

void Slider::OnMouseEnter(wxMouseEvent& event)
{
	m_isHovered = true;
	Refresh();
}

void Slider::OnMouseLeave(wxMouseEvent& event)
{
	m_isHovered = false;
	Refresh();
}

void Slider::OnMouseLeftUp(wxMouseEvent& event)
{
	if (m_isDragging) {
		m_isDragging = false;

		if (HasCapture()) {
			ReleaseMouse();
		}

		if (!m_isHovered) Refresh();
	}
}

void Slider::OnMouseLeftDown(wxMouseEvent& event)
{
	wxSize size = GetSize();

	wxSize rectSize(size.y, size.y);
	wxPoint rectPos(m_value * (size.x - size.y), 0);

	wxRect rect(rectPos, rectSize);

	if (rect.Contains(event.GetPosition())) {
		m_isDragging = true;
		if (!HasCapture()) {
			CaptureMouse();
		}
	}
	else {
		if (event.GetPosition().x >= size.y / 2 && event.GetPosition().x < size.x - size.y / 2) {
			double value = (double)(event.GetPosition().x - size.y / 2) / (double)(size.x - size.y);
			if (m_value != std::round(value * 100.0) / 100.0) {
				m_value = std::round(value * 100.0) / 100.0;
				if (m_callback) m_callback(m_value);
				Refresh();
			}
		}
		else if (event.GetPosition().x < size.y) {
			if (m_value != 0) {
				m_value = 0;
				if (m_callback) m_callback(m_value);
				Refresh();
			}
		}
		else if (event.GetPosition().x > size.x - size.y / 2) {
			if (m_value != 1) {
				m_value = 1;
				if (m_callback) m_callback(m_value);
				Refresh();
			}
		}
	}
}

void Slider::OnMouseMove(wxMouseEvent& event)
{
	if (HasCapture()) {
		wxSize size = GetSize();

		if (event.GetPosition().x >= size.y / 2 && event.GetPosition().x < size.x - size.y / 2) {
			double value = (double)(event.GetPosition().x - size.y / 2) / (double)(size.x - size.y);
			if (m_value != std::round(value * 100.0) / 100.0) {
				m_value = std::round(value * 100.0) / 100.0;
				if (m_callback) m_callback(m_value);
				Refresh();
			}
		}
		else if (event.GetPosition().x < size.y) {
			if (m_value != 0) {
				m_value = 0;
				if (m_callback) m_callback(m_value);
				Refresh();
			}
		}
		else if (event.GetPosition().x > size.x - size.y / 2) {
			if (m_value != 1) {
				m_value = 1;
				if (m_callback) m_callback(m_value);
				Refresh();
			}
		}
	}
}

BEGIN_EVENT_TABLE(Slider, wxPanel)
	EVT_PAINT(Slider::OnPaint)
	EVT_LEAVE_WINDOW(Slider::OnMouseLeave)
	EVT_ENTER_WINDOW(Slider::OnMouseEnter)
	EVT_LEFT_UP(Slider::OnMouseLeftUp)
	EVT_LEFT_DOWN(Slider::OnMouseLeftDown)
	EVT_MOTION(Slider::OnMouseMove)
END_EVENT_TABLE()