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
	std::queue<Camera::EffectInfo> Camera::mEffectQueue;
	Image* Camera::mCutton = nullptr;
	float Camera::mCuttonAlpha = 0.0f;

	void Camera::Initialize()
	{
		WindowData winData = Application::GetInstance().GetWindowData();
		mResolution.y = winData.height;
		mResolution.x = winData.width;
		mLookPosition = (mResolution / 2.0f);

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

		if (mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		if (!mEffectQueue.empty())
		{
			EffectInfo& info = mEffectQueue.front();
			info.time += Time::DeltaTime();
			float ratio = (info.time / info.duration);

			if (ratio >= 1.0f)
			{
				ratio = 1.0f;
				mEffectQueue.pop();
			}

			if (eCameraEffect::Fade_In == info.effect)
				mCuttonAlpha = 1.0f - ratio;
			else if (eCameraEffect::Fade_Out == info.effect)
				mCuttonAlpha = ratio;
			else
				mCuttonAlpha = 0.0f;
		}


		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = 0;
		tFunc.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		AlphaBlend(hdc, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, mCutton->GetHdc()
			, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, tFunc);
	}

	void Camera::PushEffect(eCameraEffect effect, float duration)
	{
		EffectInfo info = {};
		info.time = 0.0f;
		info.effect = effect;
		info.duration = duration;

		mEffectQueue.push(info);
	}

}