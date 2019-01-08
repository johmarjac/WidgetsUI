#include "stdafx.h"
#include "Button.h"

Button::Button(Widget * parent, void(*clickCallback) (void), std::wstring text)
{
	Parent = parent;
	ButtonClickCallback = clickCallback;
	Text = text;
	HoverBackgroundColor = WColor(.05f, .05f, .05f, 1);
	IdleBackgroundColor = WColor(.1f, .1f, .1f, 1);
	ClickBackgroundColor = WColor(.025f, .025f, .025f, 1);
}

void Button::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONUP)
	{
		if (HoverState == HoverState::Hover)
		{
			ButtonClickCallback();
		}

		bIsButtonBeingPressed = false;
	}

	if (message == WM_LBUTTONDOWN)
	{
		if (HoverState == HoverState::Hover)
		{
			bIsButtonBeingPressed = true;
		}
	}

	Widget::WndProc(hWnd, message, wParam, lParam);
}

void Button::Update()
{
	Widget::Update();
}

void Button::Draw(ICanvas * canvas)
{
	auto absolutePosition = GetAbsolutePosition();

	if (bIsButtonBeingPressed)
	{
		canvas->DrawFilledRect(absolutePosition.X, absolutePosition.Y, Size.X, Size.Y, WColor(ClickBackgroundColor.R, ClickBackgroundColor.G, ClickBackgroundColor.B, ClickBackgroundColor.A));
	}
	else
	{
		if (HoverState == HoverState::Hover)
			canvas->DrawFilledRect(absolutePosition.X, absolutePosition.Y, Size.X, Size.Y, WColor(HoverBackgroundColor.R, HoverBackgroundColor.G, HoverBackgroundColor.B, HoverBackgroundColor.A));
		else
			canvas->DrawFilledRect(absolutePosition.X, absolutePosition.Y, Size.X, Size.Y, WColor(IdleBackgroundColor.R, IdleBackgroundColor.G, IdleBackgroundColor.B, IdleBackgroundColor.A));
	}

	WVector2 textSize;
	canvas->GetTextSize(Text, &textSize.X, &textSize.Y);

	canvas->DrawString(Text, absolutePosition.X + (Size.X * 0.5f) - (textSize.X * 0.5f), absolutePosition.Y + (Size.Y * 0.5f) - (textSize.Y * 0.5f), WColor(1, 1, 1, 1));

	Widget::Draw(canvas);
}

Button::~Button()
{
}
