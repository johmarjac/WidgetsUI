#pragma once
#include "Widget.h"

#define DefaultCheckedText				L"Enabled"
#define DefaultUncheckedText			L"Disabled"
#define WDefaultBackgroundColor			WColor(0, 0, 0, 0);
#define DefaultCheckedColor				WColor(0, 1, 0, 1);
#define DefaultUncheckedColor			WColor(1, 0, 0, 1);
#define DefaultBackgroundHoverColor		WColor(0.05f, 0.05f, 0.05f, 1);

class ToggleTextWidget : public Widget
{
public:
	ToggleTextWidget(Widget * parent, bool * pToggleState, std::wstring text = L"DefaultText");
	virtual ~ToggleTextWidget();

public:
	std::wstring Text;
	std::wstring CheckedText;
	std::wstring UncheckedText;
	WColor BackgroundColor;
	WColor ForegroundColor;
	WColor CheckedColor;
	WColor UncheckedColor;
	WColor BackgroundHoverColor;

public:
	void Toggle();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Update() override;
	virtual void Draw(ICanvas * canvas) override;

private:
	bool bIsChecked;
	bool * pToggleState;
};
