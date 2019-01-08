#pragma once
#include "Widget.h"

class TabPage :	public Widget
{
public:
	TabPage(Widget * parent);
	virtual ~TabPage();

public:
	std::wstring PageName;

};
