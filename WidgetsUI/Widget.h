#pragma once
#include "ICanvas.hpp"
#include "Structs.h"

#include <vector>

class Widget
{
public:
	enum HoverState { Idle, Hover };

public:
	Widget();
	Widget(Widget * pParentWidget);
	virtual ~Widget();

public:
	
	/// Widgets Identifier
	std::wstring Name;

	/// Whether the Widget is Enabled or Disabled
	bool Enabled;

	/// Widgets Parent Widget
	Widget * Parent;

	/// Widgets Relative Position
	WVector2 Position;

	/// Widgets Size
	WVector2 Size;

	/// Absolute Cursor Position
	WVector2 CursorPosition;

	/// Widgets HoverState
	HoverState HoverState;

	/// Widgets Client Area Offset
	WVector2 ClientAreaOffset;

private:
	std::vector<Widget*> ChildWidgets;

public:
	bool AddWidget(Widget * pWidget);
	const Widget * GetWidgetByName(std::wstring name);

	/// Gets whether the Cursors Position is inside the given Rectangle
	bool IsCursorInsideRectangle(WRectangle rectangle, bool relativePosition = true);

	/// Gets the Widgets Absolute Position
	WVector2 GetAbsolutePosition();

	Widget * SetEnabled( bool enabled );
	Widget * SetSize( int x, int y );
	Widget * SetSize( WVector2 size );
	Widget * SetPosition( int x, int y );
	Widget * SetPosition( WVector2 position );

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Update();
	virtual void Draw(ICanvas* canvas);
};
