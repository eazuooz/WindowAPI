#include "yaPlayer.h"

#include "yaTime.h"
#include "yaInputManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaImage.h"

#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaCamera.h"

#include "yaMissile.h"

namespace ya
{
	Player::Player()
		: mSpeed(100.0f)
		, mShotTime(0.0f)
	{
		AddComponent(new Collider());
		AddComponent(new Animator());

		GetCollider()->SetScale(Vector2(50.f, 50.f));
		GetCollider()->SetOffset(Vector2(0.f, 25.f));
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		

		// 키입력에 따른 이동
		Vector2 vPos = GetPos();

		// 시간 동기화
		if (KEY_PREESED(KEY_CODE::W))
		{
			vPos.y -= mSpeed * Time::DeltaTime();
		}

		if (KEY_PREESED(KEY_CODE::S))
		{
			vPos.y += mSpeed * Time::DeltaTime();
		}

		if (KEY_PREESED(KEY_CODE::A))
		{
			vPos.x -= mSpeed * Time::DeltaTime();
		}

		if (KEY_PREESED(KEY_CODE::D))
		{
			vPos.x += mSpeed * Time::DeltaTime();
		}

		if (KEY_PREESED(KEY_CODE::SPACE))
		{
			if (mShotTime >= 0.1f)
			{
				// 미사일 쏘기
				Scene* pCurScene = SceneManager::GetPlayScene();
				Missile* pMissile = new Missile();

				pMissile->SetPos(GetPos());
				pMissile->SetScale(Vector2(20.f, 20.f));

				pCurScene->AddObject(pMissile, eColliderLayer::PlayerProjecttile);

				mShotTime = 0.f;
			}
		}
		mShotTime += Time::DeltaTime();


		
		SetPos(vPos);

		Object::Tick();
	}

	void Player::Render(HDC hdc)
	{
		

		Image* pImage = Resources::Load<Image>(L"PlayerImage", L"..\\Resources\\Images\\Fighter.bmp");
		//Image* pImage = Resources::Find<Image>(L"PlayerImage");

		if (nullptr == pImage)
			return;

		Vector2 vPos = GetPos();
		vPos = Camera::CalulatePos(vPos);

		//SetPos(vPos);

		//BitBlt(hdc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetDC(), 0, 0, SRCCOPY);
		TransparentBlt(hdc, (int)vPos.x - pImage->GetWidth() / 2
			, (int)vPos.y - pImage->GetHeight() / 2
			, pImage->GetWidth(), pImage->GetHeight()
			, pImage->GetDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));

		//Resource* p = pImage;

		//delete p;

		Object::Render(hdc);
	}
}