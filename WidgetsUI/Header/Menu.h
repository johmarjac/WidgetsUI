#pragma once
#include "Widget.h"

#define DefaultBackgroundColor			WColor(.15f, .15f, .15f, 1)
#define DefaultForegroundColor			WColor(1, 1, 1, 1)
#define DefaultTitleBackgroundColor		WColor(0.05f, 0.05f, 0.05f, 1);

#define TitleHeight						35

class Menu : public Widget
{
public:
	Menu();
	virtual ~Menu();

public:
	WColor BackgroundColor;
	WColor ForegroundColor;
	WColor TitleBackgroundColor;
	std::wstring Title;

public:
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Update() override;
	virtual void Draw(ICanvas* canvas) override;

private:
	bool bIsBeingDragged;
	WVector2 vecDragStartOffset;
};
