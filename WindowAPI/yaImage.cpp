#include "yaImage.h"

#include "yaApplication.h"
#include "yaResources.h"

namespace ya
{
	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		Image* image = Resources::Find<Image>(key);
		if (image != nullptr)
		{
			MessageBox(nullptr, L"중복 키 발생", L"이미지 생성 실패", MB_OK);
			return nullptr;
		}
		
		// 새로 생성한 비트맵을 가리키는 전용 DC 생성
		// 새로 생성한 비트맵과 DC 를 서로 연결
		image = new Image();
		HDC mainHdc = Application::GetInstance().GetHdc();

		image->mHBitmap= CreateCompatibleBitmap(mainHdc, width, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		if (0 == image->mHBitmap || 0 == image->mHdc)
			return nullptr;

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mHBitmap);
		DeleteObject(defaultBitmap);

		// 비트맵 정보 확인
		BITMAP bitmap = {};
		GetObject(image->mHBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;

		image->SetKey(key);
		Resources::Insert<Image>(key, image);

		return image;
	}

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
		mBitmap = tBitInfo.bmBits;

		int iErr = GetLastError();

		HDC hMainDC = Application::GetInstance().GetHdc();
		mHdc = CreateCompatibleDC(hMainDC);

		HBITMAP hPrevBit = (HBITMAP)SelectObject(mHdc, mHBitmap);
		DeleteObject(hPrevBit);

		return S_OK;
	}

	Pixel Image::GetPixel(int x, int y)
	{
		y = mHeight - (y + 1);

		Pixel* pPixel = (Pixel*)mBitmap;
		pPixel += (mWidth * y + x);
		return *pPixel;
	}

	void Image::SetPixel(int x, int y, Pixel pixel)
	{
		// 비트맵 좌표는 좌측 상단이 0,0 이기떄문에 윈도우 좌표에서
		// 사용하려면 y를 반대로 바꾸어주어햔다.
		y = mHeight - (y + 1);

		Pixel* pPixel = (Pixel*)mBitmap;
		pPixel += (mWidth * y + x);
		*pPixel = pixel;
	}

}
