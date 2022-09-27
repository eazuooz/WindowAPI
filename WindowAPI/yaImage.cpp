#include "yaImage.h"

#include "yaApplication.h"

namespace ya
{
	Image::Image()
		: mHBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Image::~Image()
	{
		DeleteDC(mHdc);
		DeleteObject(mHBitmap);
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mHBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (nullptr == mHBitmap)
		{
			return E_FAIL;
		}

		// 비트맵 정보 확인
		BITMAP tBitInfo = {};
		GetObject(mHBitmap, sizeof(BITMAP), &tBitInfo);

		mWidth = tBitInfo.bmWidth;
		mHeight = tBitInfo.bmHeight;


		int iErr = GetLastError();

		HDC hMainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(hMainDC);

		HBITMAP hPrevBit = (HBITMAP)SelectObject(mHdc, mHBitmap);
		DeleteObject(hPrevBit);

		return S_OK;
	}
}
