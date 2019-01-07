#pragma once

struct WColor
{

	float R;
	float G;
	float B;
	float A;

	WColor()
	{
	}

	WColor(float r, float g, float b, float a) : R(r), G(g), B(b), A(a)
	{
	}
};

struct WVector2
{
	float X;
	float Y;

	WVector2() : X(0), Y(0)
	{
	}

	WVector2(float x, float y) : X(x), Y(y)
	{
	}
};

struct WRectangle
{
	WVector2 Position;
	WVector2 Size;
};