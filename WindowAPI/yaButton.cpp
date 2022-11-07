#include "yaButton.h"
#include "yaInputManager.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	Button::Button(eUIType type)
		: UIBase(type)
	{

	}

	Button::~Button()
	{

	}

	void Button::OnInit()
	{
		mImage = Resources::Load<Image>(L"BUTTON", L"..\\Resources\\Images\\HPBAR.bmp");
		SetPos(Vector2(200.0f, 200.0f));
		SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));

		mOnClick = std::bind(&Button::Click, this);
	}

	void Button::OnActive()
	{
		UIBase::OnActive();
	}

	void Button::OnInActive()
	{
	}

	void Button::OnTick()
	{
		Vector2 mousePos = InputManager::GetMousPosition();
		Vector2 size = GetSize();

		if (mRenderPos.x <= mousePos.x && mousePos.x <= mRenderPos.x + size.x
			&& mRenderPos.y <= mousePos.y && mousePos.y <= mRenderPos.y + size.y)
			mbMouseOn = true;
		else
			mbMouseOn = false;

		if (KEY_DOWN(KEY_CODE::LBTN))
		{
			if (mbMouseOn)
			{
				mOnClick();
			}
		}
	}

	void Button::OnRender(HDC hdc)
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

	void Button::OnClear()
	{
	}

	void Button::Click()
	{
		int a = 0;
	}
}
