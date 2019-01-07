#include "stdafx.h"
#include "DropMenu.h"

DropMenu::DropMenu(Widget * parent, std::vector<Option> options, int * selectedOptionOut, const PTCHAR text)
{
	Parent = parent;
	Text = text;
	SelectedOption = selectedOptionOut;
	Options = options;

}

void DropMenu::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_LBUTTONUP)
	{
		WRectangle rect;
		rect.Position = Position;
		rect.Size = Size;

		if (IsCursorInsideRectangle(rect, true))
			Selector();
		else
		{
			if(Open)
			{
				for(unsigned int i = 0; i < Options.size(); i++)
				{
					if(IsCursorInsideRectangle(*Options[i].Rect, false))
					{
						*SelectedOption = i;
						Text = Options[i].Text;

						for(unsigned int i = 0; i < Options.size(); i++)
						{
							Option Option = Options[i];
							delete Option.Rect;
						}

						Open = false;
					}
				}
			}
		}
	}

	Widget::WndProc(hWnd, message, wParam, lParam);
}

void DropMenu::Update()
{
	Widget::Update();
}

void DropMenu::Selector()
{
	for(unsigned int i = 0; i < Options.size(); i++)
	{
		WRectangle * Rect = new WRectangle;
		Options[i].Rect = Rect;
	}

	Open = true;
}

void DropMenu::Draw(ICanvas * canvas)
{
	auto absolutePosition = GetAbsolutePosition();

	if(HoverState == HoverState::Hover)
		canvas->DrawFilledRect(absolutePosition.X, absolutePosition.Y, Size.X, Size.Y, WColor(.05f, .05f, .05f, 1));
	else
		canvas->DrawFilledRect(absolutePosition.X, absolutePosition.Y, Size.X, Size.Y, WColor(.1f, .1f, .1f, 1));

	WVector2 textSize;
	canvas->GetTextSize(Text, &textSize.X, &textSize.Y);

	canvas->DrawString(Text, absolutePosition.X + (Size.X * 0.5f) - (textSize.X * 0.5f), absolutePosition.Y + (Size.Y * 0.5f) - (textSize.Y * 0.5f), WColor(1, 1, 1, 1));
		
	if(Open)
	{
		for(unsigned int i = 0; i < Options.size(); i++)
		{
			Option Option = Options[i];

			Option.Rect->Position = absolutePosition;
			Option.Rect->Size = Size;

			Option.Rect->Position.Y = absolutePosition.Y + Size.Y + (Size.Y * i);

			canvas->DrawFilledRect(Option.Rect->Position.X, Option.Rect->Position.Y, Size.X, Size.Y, WColor(.1f, .1f, .1f, 1));

			WVector2 TextSize;
			canvas->GetTextSize(Option.Text, &TextSize.X, &TextSize.Y);

			canvas->DrawString(Option.Text, Option.Rect->Position.X + (Option.Rect->Size.X / 2) - (TextSize.X / 2), Option.Rect->Position.Y + (Option.Rect->Size.Y / 2) - (TextSize.Y / 2), WColor(1, 1, 1, 1));
		}
	}

	Widget::Draw(canvas);
}

DropMenu::~DropMenu()
{
}