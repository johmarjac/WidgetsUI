#pragma once
#include "Widget.h"

#define WDefaultBackgroundColor			WColor(.15f, .15f, .15f, 1)
#define WDefaultForegroundColor			WColor(1, 1, 1, 1)
#define WDefaultTitleBackgroundColor		WColor(0.05f, 0.05f, 0.05f, 1);

#define WTitleHeight						35

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
	Menu * SetTitle( std::wstring title );

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Update() override;
	virtual void Draw(ICanvas* canvas) override;

private:
	bool bIsBeingDragged;
	WVector2 vecDragStartOffset;
};
