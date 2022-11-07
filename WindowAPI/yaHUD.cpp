#include "yaHUD.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	HUD::HUD(eUIType type)
		: UIBase(type)
	{
	}
	HUD::~HUD()
	{
	}
	void HUD::OnInit()
	{
		mImage = Resources::Load<Image>(L"HPBAR", L"..\\Resources\\Images\\HPBAR.bmp");
		SetPos(Vector2(100.0f, 100.0f));
		SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));
	}
	void HUD::OnActive()
	{
	}
	void HUD::OnInActive()
	{
	}

	void HUD::OnTick()
	{
		
	}

	void HUD::OnRender(HDC hdc)
	{
		if (nullptr == mImage)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mRenderPos.x
			, (int)mRenderPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void HUD::OnClear()
	{
	}
}
