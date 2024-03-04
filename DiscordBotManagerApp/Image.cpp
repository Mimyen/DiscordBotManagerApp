#include "Image.h"

Image::Image(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, wxString path)
	: wxPanel(parent, id, pos, size), defaultPos(pos), defaultSize(size)
{
    // Initialize handlers, load image and bind redrawing function
    wxInitAllImageHandlers();

    if (!image.LoadFile(path, wxBITMAP_TYPE_PNG)) {
        wxLogError("Couldn't load show.png");
    }

    Bind(wxEVT_PAINT, &Image::OnPaint, this);
}

void Image::Resize(wxSize windowSize, wxSize defaultWindowSize)
{
    // Calculate new size of the element
    int imageWidth = defaultSize.x * windowSize.x / defaultWindowSize.x;
    int imageHeight = defaultSize.y * windowSize.y / defaultWindowSize.y;
    int imageX = defaultPos.x * windowSize.x / defaultWindowSize.x;
    int imageY = defaultPos.y * windowSize.y / defaultWindowSize.y;

    // Set the new position and size for the button
    SetSize(imageX, imageY, imageWidth, imageHeight);

    Refresh();
}

void Image::OnPaint(wxPaintEvent& event)
{
    // Initialize repainting
    wxPaintDC dc(this);
    Render(dc);
}

void Image::Render(wxDC& dc)
{
    // Get size of the component
    wxSize size = GetClientSize();

    // Create a copy of an image
    wxImage img = image;

    // Scale down the bitmap to the original size for antialiasing effect
    img.Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH);

    wxBitmap finalBmp(img);

    // Draw the bitmap on the device context
    dc.DrawBitmap(finalBmp, 0, 0, true);
}