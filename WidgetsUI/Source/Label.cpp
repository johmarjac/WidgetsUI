#include "stdafx.h"
#include "Label.h"

Label::Label(Widget * parent, std::wstring text)
{
	Parent = parent;
	Text = text;
	TextColor = WColor(1, 1, 1, 1);
}

void Label::Draw(ICanvas * canvas)
{
	const auto absolutePos = GetAbsolutePosition();

	canvas->DrawString(Text, absolutePos.X, absolutePos.Y, WColor(TextColor.R, TextColor.G, TextColor.B, TextColor.A));

	Widget::Draw(canvas);
}

Label::~Label()
{
}
