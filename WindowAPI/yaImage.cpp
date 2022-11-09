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
			MessageBox(nullptr, L"�ߺ� Ű �߻�", L"�̹��� ���� ����", MB_OK);
			return nullptr;
		}
		
		// ���� ������ ��Ʈ���� ����Ű�� ���� DC ����
		// ���� ������ ��Ʈ�ʰ� DC �� ���� ����
		image = new Image();
		HDC mainHdc = Application::GetInstance().GetHdc();

		image->mHBitmap= CreateCompatibleBitmap(mainHdc, width, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		if (0 == image->mHBitmap || 0 == image->mHdc)
			return nullptr;

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mHBitmap);
		DeleteObject(defaultBitmap);

		// ��Ʈ�� ���� Ȯ��
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

		// ��Ʈ�� ���� Ȯ��
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
		// ��Ʈ�� ��ǥ�� ���� ����� 0,0 �̱⋚���� ������ ��ǥ����
		// ����Ϸ��� y�� �ݴ�� �ٲپ��־��h��.
		y = mHeight - (y + 1);

		Pixel* pPixel = (Pixel*)mBitmap;
		pPixel += (mWidth * y + x);
		*pPixel = pixel;
	}

}
