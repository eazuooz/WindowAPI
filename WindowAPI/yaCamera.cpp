#include "yaCamera.h"
#include "yaApplication.h"
#include "yaInputManager.h"
#include "yaTime.h"
#include "yaObject.h"

namespace ya
{
	Size Camera::mResolution = {};		// 화면 해상도
	Vector2 Camera::mLookPosition = {};  // 카메라가 보고있는 좌표
	Vector2 Camera::mDistance = {};		// 화면 해상도 중심 좌표와 현재 카메라 Look 간의 차이
	Object* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		WindowData winData = Application::GetInstance().GetWindowData();
		mResolution.y = winData.height; 
		mResolution.x = winData.width;
		mLookPosition = (mResolution / 2.0f);

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

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

}