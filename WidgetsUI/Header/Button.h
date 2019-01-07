#pragma once
#include "Widget.h"

class Button : public Widget
{
public:
	Button(Widget * parent, void(*clickCallback) (void), std::wstring text);
	virtual ~Button();

public:
	std::wstring Text;
	WColor HoverBackgroundColor;
	WColor IdleBackgroundColor;
	WColor ClickBackgroundColor;

private:
	bool bIsButtonBeingPressed;

public:
	void(*ButtonClickCallback)(void);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Update() override;
	virtual void Draw(ICanvas * canvas) override;
};

