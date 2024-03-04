#include "Sizer.h"

void Sizer::SetDefaultSize(wxSize size)
{
	this->defaultSize = size;
}

void Sizer::AddObject(wxWindow* object)
{
    objects.push_back(object);
}

void Sizer::Resize()
{
    wxSize sizeOfWindow;
    for (wxWindow* object : objects) {
        // Get the new size of the frame
        sizeOfWindow = object->GetClientSize();
        wxSize size = object->GetSize();
        wxPoint position = object->GetPosition();

        int buttonX = size.x * sizeOfWindow.x / defaultSize.x; // Calculate new X position
        int buttonY = size.y * sizeOfWindow.y / defaultSize.y; // Calculate new Y position
        int buttonWidth = position.x * sizeOfWindow.x / defaultSize.x; // Calculate new width
        int buttonHeight = position.y * sizeOfWindow.y / defaultSize.y; // Calculate new height

        // Set the new position and size for the button
        object->SetSize(buttonX, buttonY, buttonWidth, buttonHeight);
        object->Refresh();

    }
    defaultSize = sizeOfWindow;
}

Sizer::Sizer(wxSize size)
{
    this->defaultSize = size;
}
