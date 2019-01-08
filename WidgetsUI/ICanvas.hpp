#pragma once
#include "stdafx.h"
#include "Structs.h"

class ICanvas
{
public:
	virtual ~ICanvas() {}

	virtual void DrawLine(float startX, float startY, float endX, float endY, WColor color, float thickness = 1) = 0;
	virtual void DrawFilledRect(float x, float y, float width, float height, WColor color) = 0;
	virtual void DrawRect(float x, float y, float width, float height, WColor color, float thickness = 1) = 0;
	virtual void DrawString(std::wstring text, float x, float y, WColor color) = 0;
	virtual void GetTextSize(std::wstring text, float * outX, float * outY) = 0;
};