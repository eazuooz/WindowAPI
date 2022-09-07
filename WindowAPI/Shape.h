#pragma once
#include <Windows.h>

class Shape
{
public:
	Shape()
		: mPos({0, 0})
		, mSize({ 0, 0 })
	{

	}
	~Shape()
	{

	}

	void SetPos(int y, int x)
	{
		mPos.y = y;
		mPos.x = x;
	}
	POINT GetPos() { return mPos; }
	void SetSize(int y, int x)
	{
		mSize.y = y;
		mSize.x = x;
	}
	POINT GetSize() { return mSize; }

private:
	POINT mPos;
	POINT mSize;
};

