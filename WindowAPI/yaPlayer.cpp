#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInputManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaApplication.h"

#include "yaMissile.h"

namespace ya
{
	Player::Player()
		: mSpeed(100.0f)
		, mShotTime(0.0f)
		, mImageBit(NULL)
		, mImageDC(NULL)
	{
		mImageBit = (HBITMAP)LoadImageW(nullptr, L"..\\Resources\\Fighter.bmp"
			, IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP tBitInfo = {};
		GetObject(mImageBit, sizeof(BITMAP), &tBitInfo);

		int iErr = GetLastError();

		HDC hMainDC = Application::GetInstance().GetWindowData().hdc;
		mImageDC = CreateCompatibleDC(hMainDC);

		HBITMAP hPrevBit = (HBITMAP)SelectObject(mImageDC, mImageBit);
		DeleteObject(hPrevBit);
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

	void Player::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		BitBlt(hdc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, mImageDC, 0, 0, SRCCOPY);
	}
}