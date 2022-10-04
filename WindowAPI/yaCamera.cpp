#include "yaCamera.h"
#include "yaApplication.h"
#include "yaInputManager.h"
#include "yaTime.h"
#include "yaObject.h"

namespace ya
{
	Size Camera::mResolution = {};		// ȭ�� �ػ�
	Vector2 Camera::mLookPosition = {};  // ī�޶� �����ִ� ��ǥ
	Vector2 Camera::mDistance = {};		// ȭ�� �ػ� �߽� ��ǥ�� ���� ī�޶� Look ���� ����
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
		// �ð� ����ȭ
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