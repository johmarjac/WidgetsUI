#pragma once
#include "Widget.h"
#include "TabPage.h"

#define PageNameWidth	70
#define PageNameHeight	25

class TabControl : public Widget
{
public:
	TabControl(Widget * parent);
	virtual ~TabControl();

public:
	std::vector<TabPage*> Pages;
	TabPage* CurrentPage;

public:
	void AddPage(TabPage * page);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Update();
	virtual void Draw(ICanvas * canvas);
};
