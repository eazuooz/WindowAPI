#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInputManager.h"

#include "yaScene.h"
#include "yaSceneManager.h"

#include "yaMissile.h"

namespace ya
{
	Player::Player()
		: mSpeed(100.0f)
		, mShotTime(0.0f)
	{
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
				Scene* pCurScene = SceneManager::GetInstance().GetPlayScene();
				Missile* pMissile = new Missile();

				pMissile->SetPos(GetPos());
				pMissile->SetScale(Vector2(20.f, 20.f));

				pCurScene->AddObject(pMissile);

				mShotTime = 0.f;
			}
		}
		mShotTime += Time::DeltaTime();

		SetPos(vPos);
	}
}