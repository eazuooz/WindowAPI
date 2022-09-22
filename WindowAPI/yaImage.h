#pragma once
#include "yaResource.h"

namespace ya
{
	class Image : public Resource
	{
	public:
		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

	public:
		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP     mHBitmap;
		HDC         mHdc;
		UINT        mWidth;
		UINT        mHeight;
	};
}
