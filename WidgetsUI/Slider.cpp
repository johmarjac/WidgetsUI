#include "stdafx.h"
#include "Slider.h"

Slider::Slider(Widget * parent, int * pValue, int minValue, int maxValue)
{
	Parent = parent;
	MinValue = minValue;
	MaxValue = maxValue;
	Value = pValue;
	BackgroundColor = WColor(.1f, .1f, .1f, 1);
	SliderColor = WColor(.025f, .025f, .025f, 1);
}

void Slider::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN)
	{
		if (!bIsBeingSlided)
		{
			if (IsCursorInsideRectangle(GetCurrentSliderRectangle(), false))
			{
				bIsBeingSlided = true;
			}
		}
	}

	const auto absolutePos = GetAbsolutePosition();

	if (bIsBeingSlided)
	{
		auto percent = GetPercentInRangeByValue((int)absolutePos.X, (int)absolutePos.X + (int)Size.X, (int)CursorPosition.X);
		if (percent < 0)
			percent = 0;
		else if (percent > 100)
			percent = 100;

		*Value = GetValueInRangeByPercent(MinValue, MaxValue, percent);
	}

	if (message == WM_LBUTTONUP)
		bIsBeingSlided = false;

	Widget::WndProc(hWnd, message, wParam, lParam);
}

void Slider::Update()
{
	Widget::Update();
}

void Slider::Draw(ICanvas * canvas)
{
	const auto absolutePos = GetAbsolutePosition();

	// Background
	canvas->DrawFilledRect(absolutePos.X, absolutePos.Y + 5, Size.X, Size.Y - 10, WColor(BackgroundColor.R, BackgroundColor.G, BackgroundColor.B, BackgroundColor.A));
	
	auto slider = GetCurrentSliderRectangle();

	// Draw Slider
	canvas->DrawFilledRect(slider.Position.X, absolutePos.Y, 10, Size.Y, WColor(SliderColor.R, SliderColor.G, SliderColor.B, SliderColor.A));

	Widget::Draw(canvas);
}

int Slider::GetPercentInRangeByValue(int min, int max, int value)
{
	return ((value - min) * 100) / (max - min);
}

int Slider::GetValueInRangeByPercent(int min, int max, int percent)
{
	return ((percent * (max - min) / 100) + min);
}

WRectangle Slider::GetCurrentSliderRectangle()
{	
	// Get Percent between a custom range ((input - min) * 100) / (max - min)
	// Get Value by Percent between a custom range ((percent * (max - min) / 100) + min

	const auto absolutePos = GetAbsolutePosition();
	auto percentage = GetPercentInRangeByValue(MinValue, MaxValue, *Value);
	auto sliderPosX = GetValueInRangeByPercent((int)absolutePos.X, (int)absolutePos.X + (int)Size.X, (int)percentage);
	
	WRectangle rect;
	rect.Position = WVector2((float)(sliderPosX - 5), absolutePos.Y);
	rect.Size = WVector2(10, Size.Y);

	return rect;
}

Slider::~Slider()
{
}
