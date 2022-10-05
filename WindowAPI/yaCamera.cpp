#include "yaCamera.h"
#include "yaApplication.h"
#include "yaInputManager.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaImage.h"

namespace ya
{
	/// <summary>
	/// Camera Move
	/// </summary>
	Size Camera::mResolution = {};		
	Vector2 Camera::mLookPosition = {}; 
	Vector2 Camera::mDistance = {};		
	Object* Camera::mTarget = nullptr;

	/// <summary>
	/// Fade in out effect
	/// </summary>
	eCameraEffect Camera::mEffect = eCameraEffect::None;
	Image* Camera::mCutton = nullptr;
	float Camera::mCuttonAlpha = 1.0f;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 5.0f;

	void Camera::Initialize()
	{
		WindowData winData = Application::GetInstance().GetWindowData();
		mResolution.y = winData.height; 
		mResolution.x = winData.width;
		mLookPosition = (mResolution / 2.0f);

		mEffect = eCameraEffect::Fade_In;
		mCutton = Image::Create(L"Cutton", winData.width, winData.height);
	}
	void Camera::Tick()
	{
		// 시간 동기화
		if (KEY_PREESED(KEY_CODE::UP))
		{
			mLookPosition.y -= Time::DeltaTime() * 500.0f;
		}

		if (KEY_PREESED(KEY_CODE::DOWN))
		{
			mLookPosition.y += Time::DeltaTime() * 500.0f;
		}

		if (KEY_PREESED(KEY_CODE::LEFT))
		{
			mLookPosition.x -= Time::DeltaTime() * 500.0f;
		}

		if (KEY_PREESED(KEY_CODE::RIGHT))
		{
			mLookPosition.x += Time::DeltaTime() * 500.0f;
		}

		if(mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		// Alpha 1 -> 0, 5초에 걸쳐서
		if (mAlphaTime <= 5.f)
		{
			mAlphaTime += Time::DeltaTime();
			float fRatio = (mAlphaTime / mEndTime);	// 제한 시간 대비 진행시간의 비율을 0 ~ 1 사이로 환산

			if (eCameraEffect::Fade_In == mEffect)
				mCuttonAlpha = 1.f - fRatio;
			else
				mCuttonAlpha = fRatio;
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = 0;
		tFunc.SourceConstantAlpha = (BYTE)(255.f * mCuttonAlpha);

		AlphaBlend(hdc, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, mCutton->GetHdc()
			, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, tFunc);
	}

}