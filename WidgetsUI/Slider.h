#pragma once
#include "Widget.h"

class Slider : public Widget
{
public:
	Slider(Widget * parent, int * pValue, int minValue = 0, int maxValue = 100);
	virtual ~Slider();

public:
	int MinValue;
	int MaxValue;
	WColor BackgroundColor;
	WColor SliderColor;

public:
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Update() override;
	virtual void Draw(ICanvas * canvas) override;

private:
	bool bIsBeingSlided;
	int * Value;

private:
	int GetPercentInRangeByValue(int min, int max, int value);
	int GetValueInRangeByPercent(int min, int max, int percent);
	WRectangle GetCurrentSliderRectangle();
};
