#include "stdafx.h"
#include "TabControl.h"

TabControl::TabControl(Widget * parent)
{
	Parent = parent;
	Size = WVector2( Parent->Size.X, Parent->Size.Y );
	ClientAreaOffset = WVector2(0, WPageNameHeight);
}

void TabControl::AddPage(TabPage * page)
{
	if (page == nullptr)
		return;

	if (Pages.size() == 0)
		CurrentPage = page;

	Pages.push_back(page);
}

void TabControl::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONUP) 
	{
		for (unsigned int i = 0; i < Pages.size(); i++)
		{
			auto page = Pages[i];
			const auto topLeft = GetAbsolutePosition();

			if (CursorPosition.X >= (topLeft.X + (i * WPageNameWidth)) && CursorPosition.X < (topLeft.X + (i * WPageNameWidth) + WPageNameWidth)
				&& CursorPosition.Y >= topLeft.Y && CursorPosition.Y < (topLeft.Y + WPageNameHeight))
			{
				if (CurrentPage == page)
					continue;

				CurrentPage = page;
			}
		}
	}

	if (CurrentPage == nullptr)
		return;

	CurrentPage->WndProc(hWnd, message, wParam, lParam);

	Widget::WndProc(hWnd, message, wParam, lParam);
}

void TabControl::Update()
{
	if (CurrentPage == nullptr)
		return;

	CurrentPage->Update();

	Widget::Update();
}

void TabControl::Draw(ICanvas * canvas)
{
	// Draw TabPageTitles
	for(unsigned int i = 0; i < Pages.size(); i++)
	{
		auto page = Pages[i];

		// Calculate Text Size
		WVector2 pageNameSize;
		canvas->GetTextSize(page->PageName.c_str(), &pageNameSize.X, &pageNameSize.Y);

		// Calculate Position
		const auto topLeft = GetAbsolutePosition();

		// Draw the Page Background
		if (CurrentPage == page)
			canvas->DrawFilledRect(topLeft.X + (i * WPageNameWidth), topLeft.Y, WPageNameWidth, WPageNameHeight, WColor(.15f, .15f, .15f, 1));
		else
			canvas->DrawFilledRect(topLeft.X + (i * WPageNameWidth), topLeft.Y, WPageNameWidth, WPageNameHeight, WColor(.075f, .075f, .075f, 1));
		
		// Draw the Page Name
		canvas->DrawString(page->PageName.c_str(), topLeft.X + (i * WPageNameWidth) + (WPageNameWidth * 0.5f) - (pageNameSize.X * 0.5f), topLeft.Y, WColor(1, 1, 1, 1));
	}

	if (CurrentPage == nullptr)
		return;

	CurrentPage->Draw(canvas);

	Widget::Draw(canvas);
}

TabControl::~TabControl()
{
	for (auto page : Pages)
		delete page;

	Pages.clear();
}
