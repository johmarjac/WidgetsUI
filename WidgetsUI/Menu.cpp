#include "stdafx.h"
#include "Menu.h"

const int Padding = 10;
const int CloseSize = WTitleHeight - Padding;

Menu::Menu()
{
	Parent = this;
	ClientAreaOffset = WVector2(0, WTitleHeight);

	BackgroundColor = WDefaultBackgroundColor;
	ForegroundColor = WDefaultForegroundColor;
	TitleBackgroundColor = WDefaultTitleBackgroundColor;
	Title = L"DefaultTitle";
}

const Menu * Menu::SetTitle( std::wstring title )
{
	Title = title;

	return this;
}

void Menu::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN)
	{
		if (!bIsBeingDragged)
		{
			if (CursorPosition.X >= Position.X && CursorPosition.X < Position.X + Size.X
				&& CursorPosition.Y >= Position.Y && CursorPosition.Y < Position.Y + WTitleHeight)
			{
				bIsBeingDragged = true;
				vecDragStartOffset = WVector2(CursorPosition.X - Position.X, CursorPosition.Y - Position.Y);
			}
		}
	}

	if (message == WM_LBUTTONUP)
	{
		const auto absolutePos = GetAbsolutePosition();
		WRectangle rect;
		rect.Position = WVector2(absolutePos.X + Size.X - CloseSize, absolutePos.Y + Padding);
		rect.Size = WVector2(CloseSize, CloseSize);

		if (IsCursorInsideRectangle(rect, false))
			Enabled = false;
	}
	
	if (message == WM_LBUTTONUP && bIsBeingDragged)
		bIsBeingDragged = false;

	if(bIsBeingDragged)
		Position = WVector2(CursorPosition.X - vecDragStartOffset.X, CursorPosition.Y - vecDragStartOffset.Y);

	Widget::WndProc(hWnd, message, wParam, lParam);
}

void Menu::Update()
{
	Widget::Update();
}

void Menu::Draw(ICanvas * canvas)
{
	if (!Enabled)
		return;

	auto absolutePos = GetAbsolutePosition();

	// Menu Background
	canvas->DrawFilledRect(absolutePos.X, absolutePos.Y, Size.X, Size.Y, WColor(BackgroundColor.R, BackgroundColor.G, BackgroundColor.B, BackgroundColor.A));
	
	// Title Background
	canvas->DrawFilledRect(absolutePos.X, absolutePos.Y, Size.X, WTitleHeight, WColor(TitleBackgroundColor.R, TitleBackgroundColor.G, TitleBackgroundColor.B, TitleBackgroundColor.A));

	// Title Close
	canvas->DrawLine(absolutePos.X + Size.X - CloseSize, absolutePos.Y + Padding, absolutePos.X + Size.X - Padding, absolutePos.Y + CloseSize, WColor(1, 1, 1, 1));
	canvas->DrawLine(absolutePos.X + Size.X  - CloseSize, absolutePos.Y + CloseSize, absolutePos.X + Size.X - Padding, absolutePos.Y + Padding, WColor(1, 1, 1, 1));

	// Title
	WVector2 textSize;
	canvas->GetTextSize(Title.c_str(), &textSize.X, &textSize.Y);
	canvas->DrawString(Title.c_str(), 
		absolutePos.X + (Size.X * 0.5f) - (textSize.X * 0.5f), absolutePos.Y + 5,
		WColor(ForegroundColor.R, ForegroundColor.G, ForegroundColor.B, ForegroundColor.A));

	Widget::Draw(canvas);
}

Menu::~Menu()
{
}
