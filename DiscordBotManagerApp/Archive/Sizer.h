#pragma once

#include "libs.h"

class Sizer
{
public:
	void SetDefaultSize(wxSize size);
	void AddObject(wxWindow* object);
	void Resize();
	Sizer(wxSize size);

private:
	wxSize defaultSize;

	std::vector<wxWindow*> objects;
};

