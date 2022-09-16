#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInputManager.h"

namespace ya
{
	Player::Player()
		: mSpeed(100.0f)
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
		if (KEY_UP(KEY_CODE::W))
		{
			//vPos.y -= m_fSpeed * DT;
			vPos.y -= 50.f;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			vPos.y += mSpeed * Time::DeltaTime();
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			vPos.x -= mSpeed * Time::DeltaTime();
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			vPos.x += mSpeed * Time::DeltaTime();
		}




		SetPos(vPos);
	}
}