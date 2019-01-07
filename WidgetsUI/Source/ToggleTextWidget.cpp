#include "stdafx.h"
#include "ToggleTextWidget.h"

ToggleTextWidget::ToggleTextWidget(Widget * parent, bool * toggleState, std::wstring text)
{
	Parent = parent;
	Text = text;
	CheckedText = DefaultCheckedText;
	UncheckedText = DefaultUncheckedText;
	BackgroundColor = DefaultBackgroundColor;
	CheckedColor = DefaultCheckedColor;
	UncheckedColor = DefaultUncheckedColor;
	ForegroundColor = WColor(1, 1, 1, 1);
	BackgroundHoverColor = DefaultBackgroundHoverColor;
	
	pToggleState = toggleState;
	bIsChecked = *toggleState;
}

void ToggleTextWidget::Toggle()
{
	if (pToggleState == nullptr)
		return;

	*pToggleState = bIsChecked = !bIsChecked;
}

void ToggleTextWidget::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONUP && HoverState == HoverState::Hover)
	{
		Toggle();
	}

	Widget::WndProc(hWnd, message, wParam, lParam);
}

void ToggleTextWidget::Update()
{
	Widget::Update();
}

void ToggleTextWidget::Draw(ICanvas * canvas)
{
	// Background
	auto pos = GetAbsolutePosition();
	if(HoverState == HoverState::Hover)
		canvas->DrawFilledRect(pos.X, pos.Y, Size.X, Size.Y, WColor(BackgroundHoverColor.R, BackgroundHoverColor.G, BackgroundHoverColor.B, BackgroundHoverColor.A));
	else
		canvas->DrawFilledRect(pos.X, pos.Y, Size.X, Size.Y, WColor(BackgroundColor.R, BackgroundColor.G, BackgroundColor.B, BackgroundColor.A));

	// Text
	canvas->DrawString(Text.c_str(), pos.X, pos.Y, WColor(ForegroundColor.R, ForegroundColor.G, ForegroundColor.B, ForegroundColor.A));
		
	// State Text
	auto stateTextPos = GetAbsolutePosition();
	WVector2 textSize;
	if (bIsChecked)
	{
		canvas->GetTextSize(CheckedText.c_str(), &textSize.X, &textSize.Y);
		stateTextPos.X += Parent->Size.X - textSize.X;

		canvas->DrawString(CheckedText.c_str(), stateTextPos.X, stateTextPos.Y, WColor(CheckedColor.R, CheckedColor.G, CheckedColor.B, CheckedColor.A));
	}		
	else
	{
		canvas->GetTextSize(UncheckedText.c_str(), &textSize.X, &textSize.Y);
		stateTextPos.X += Parent->Size.X - textSize.X;

		canvas->DrawString(UncheckedText.c_str(), stateTextPos.X, stateTextPos.Y, WColor(UncheckedColor.R, UncheckedColor.G, UncheckedColor.B, UncheckedColor.A));
	}

	Widget::Draw(canvas);
}

ToggleTextWidget::~ToggleTextWidget()
{
}
