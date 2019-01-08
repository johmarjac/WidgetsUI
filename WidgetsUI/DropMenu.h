#pragma once
#include "Widget.h"
#include "Structs.h"

#define WDefaultBackgroundColor			WColor(.15f, .15f, .15f, 1)
#define WDefaultForegroundColor			WColor(1, 1, 1, 1)
#define WDefaultTitleBackgroundColor		WColor(0.05f, 0.05f, 0.05f, 1);

class DropMenu : public Widget
{
public:
	struct Option
	{
		PTCHAR Text;
		WRectangle* Rect;

		Option()
		{
		}

		Option(const PTCHAR string)
		{
			Text = string;
		}
	};

public:
    DropMenu(Widget * parent, std::vector<Option> options, int * selectedOptionOut, const PTCHAR text);
    virtual ~DropMenu();
	
public:
    std::wstring Text;
    int * SelectedOption;
    std::vector<Option> Options;
	bool Open = false;

public:
    virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
    virtual void Update() override;
    virtual void Draw(ICanvas * canvas) override;
	void Selector();

};