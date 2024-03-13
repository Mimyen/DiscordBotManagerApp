#pragma once

#include "libs.h"

#define LDC(x) wxLogDebug(std::to_string(x).c_str())

class Utils
{
public:
    static wxImage CreateAlphaImage(wxSize size) {
        // Create a temporary image to initialize the bitmap with transparent black pixels
        wxImage img(size.x * 2, size.y * 2);
        img.InitAlpha();
        img.SetRGB(wxRect(0, 0, size.x * 2, size.y * 2), 0, 0, 0); // Set all pixels to black

        // Set alpha channel to 0 for all pixels
        for (int i = 0; i < size.x * 2; ++i) {
            for (int j = 0; j < size.y * 2; ++j) {
                img.SetAlpha(i, j, 0);
            }
        }

        return img;
    };

    static wxBitmap CreateEmptyBitmap(wxSize size) {
        // Create a bitmap with higher resolution for antialiasing
        wxBitmap bmp(size * 2, wxBITMAP_SCREEN_DEPTH); // Keep *2 for antialiasing

        // Initialize the bitmap with the image data
        bmp = wxBitmap(Utils::CreateAlphaImage(size));

        return bmp;
    };


    template<typename T>
    static T Clamp(const T& value, const T& low, const T& high) {
        return (value < low) ? low : (value > high) ? high : value;
    };

    static wxBitmap CreateRoundedRectangleBitmap(wxDC& dc, const wxSize& size, int cornerRadius, unsigned int multiplier = 2) {
        // Create a bitmap with an alpha channel
        wxBitmap bitmap = CreateEmptyBitmap(size * multiplier / 2);

        // Create a graphics context for antialiased drawing
        wxMemoryDC memDC(&dc);
        memDC.SelectObject(bitmap);

        wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
        if (gc) {
            gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

            // Set background transparency
            gc->SetBrush(wxBrush(wxColour(0, 0, 0, 0))); // Transparent brush
            gc->DrawRectangle(0, 0, size.x * multiplier, size.y * multiplier);

            // Draw a filled rounded rectangle with antialiasing
            gc->SetBrush(wxBrush(*wxWHITE)); // White (or any color you need)
            gc->DrawRoundedRectangle(0, 0, size.x * multiplier, size.y * multiplier, cornerRadius * multiplier);

            delete gc; // Clean up the graphics context
        }
        bitmap.Rescale(bitmap, size);

        memDC.SelectObject(wxNullBitmap); // Deselect the bitmap

        // Rescale the bitmap back to the original size with antialiasing
        return bitmap;
    };

    static wxRegion GetRoundedRegion(wxDC& dc, wxSize size, int radius = 20, int multiplier = 2) {
        // Create a rounded rectangle bitmap and then a region from it
        wxBitmap roundedRectBitmap = Utils::CreateRoundedRectangleBitmap(dc, size * 2, radius, multiplier); // 10 is the corner radius
        // roundedRectBitmap.SaveFile("pawel.png", wxBITMAP_TYPE_PNG);
        return wxRegion(roundedRectBitmap, wxColour(0, 0, 0, 0), 1); // Threshold near black to treat as transparent
    };
};