#include "stdafx.h"
#include "Widget.h"

Widget::Widget() : Widget::Widget(this)
{	
}

Widget::Widget(Widget * pParentWidget) : Parent(pParentWidget)
{
	Name = L"";
	Enabled = true;
}

bool Widget::AddWidget(Widget * pWidget)
{
	if (GetWidgetByName(pWidget->Name) != nullptr)
		return false;

	ChildWidgets.emplace_back(pWidget);
	return true;
}

const Widget * Widget::GetWidgetByName(std::wstring name)
{
	for (auto widget : ChildWidgets)
	{
		if (widget->Name.empty())
			continue;

		if (widget->Name.compare(name) == 0)
			return widget;
	}

	return nullptr;
}

bool Widget::IsCursorInsideRectangle(WRectangle rectangle, bool relativePosition)
{
	auto position = rectangle.Position;
	auto absolutePosition = GetAbsolutePosition();

	if (relativePosition)
		position = WVector2(absolutePosition.X + position.X, absolutePosition.Y + position.Y);

	return 
		CursorPosition.X >= position.X && CursorPosition.X < position.X + rectangle.Size.X 
		&& 
		CursorPosition.Y >= position.Y && CursorPosition.Y < position.Y + rectangle.Size.Y;
}

WVector2 Widget::GetAbsolutePosition()
{
	if (Parent == this)
		return Position;

	auto absPos = Parent->GetAbsolutePosition();

	return WVector2(absPos.X + Position.X + Parent->ClientAreaOffset.X, absPos.Y + Position.Y + Parent->ClientAreaOffset.Y);
}

const Widget * Widget::SetSize( float x, float y )
{
	Size.X = x;
	Size.Y = y;

	return this;
}

const Widget * Widget::SetSize( WVector2 size )
{
	return SetSize( size.X, size.Y );
}

const Widget * Widget::SetPosition( float x, float y )
{
	Position.X = x;
	Position.Y = y;

	return this;
}

const Widget * Widget::SetPosition( WVector2 position )
{
	return SetPosition(position.X, position.Y);
}

void Widget::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!Enabled)
		return;

	if (message == WM_MOUSEMOVE)
	{
		auto xPos = GET_X_LPARAM(lParam);
		auto yPos = GET_Y_LPARAM(lParam);
		auto absolutePos = GetAbsolutePosition();

		CursorPosition.X = (float)xPos;
		CursorPosition.Y = (float)yPos;

		WRectangle rect;
		rect.Position = absolutePos;
		rect.Size = Size;

		if (IsCursorInsideRectangle(rect, false))
			HoverState = HoverState::Hover;
		else
			HoverState = HoverState::Idle;
	}

	for (auto widget : ChildWidgets)
		widget->WndProc(hWnd, message, wParam, lParam);
}

void Widget::Update()
{
	if (!Enabled)
		return;
	
	for (auto widget : ChildWidgets)
		widget->Update();
}

void Widget::Draw(ICanvas * canvas)
{
	if (!Enabled)
		return;

	for (auto widget : ChildWidgets)
		widget->Draw(canvas);
}

Widget::~Widget()
{
	for (auto widget : ChildWidgets)
		delete widget;

	ChildWidgets.clear();
}
