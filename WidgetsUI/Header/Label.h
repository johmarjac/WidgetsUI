#pragma once
#include "Widget.h"

class Label : public Widget
{
public:
	Label(Widget * parent, std::wstring text);
	virtual ~Label();
		
public:
	WColor TextColor;

public:
	virtual void Draw(ICanvas * canvas) override;
private:
	std::wstring Text;
};
