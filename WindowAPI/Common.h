#pragma once
#include "framework.h"

#include <assert.h>
#include <bitset>
#include <string>
#include <vector>
#include <list>
#include <map>


#include "yaMath.h"
#include "def.h"

#pragma comment(lib, "Msimg32.lib")
//using std::vector;
//using std::list;
//using std::map;
//using std::make_pair;
//using std::string;
//using std::wstring;


namespace ya
{
	using Pos = POINT;

	struct WindowData
	{
		HWND hWnd;
		HDC  hdc;
		HBITMAP backTexture;
		HDC backBuffer;
		UINT height;
		UINT width;

		void Clear()
		{
			hWnd = NULL;
			hdc = NULL;
			backTexture = NULL;
			backBuffer = NULL;
			height = 0;
			width = 0;
		}
	};

	struct Pen
	{
	private:
		HDC		mHdc;
		HPEN	mOldPen;

	public:
		Pen(HDC hdc, HPEN pen)
			: mHdc(hdc)
			, mOldPen(NULL)
		{
			mOldPen = (HPEN)SelectObject(mHdc, pen);
		}

		~Pen()
		{
			SelectObject(mHdc, mOldPen);
		}

		void SetColor(HPEN pen)
		{
			mOldPen = (HPEN)SelectObject(mHdc, pen);
		}
	};

	struct Brush
	{
	private:
		HDC		mHdc;
		HBRUSH	mOldBrush;

	public:
		Brush(HDC hdc, HBRUSH brush)
			: mHdc(hdc)
			, mOldBrush(NULL)
		{
			mOldBrush = (HBRUSH)SelectObject(mHdc, brush);
		}

		~Brush()
		{
			SelectObject(mHdc, mOldBrush);
		}
	};
}
