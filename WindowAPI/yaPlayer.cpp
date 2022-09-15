#include "yaPlayer.h"

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
		if (GetAsyncKeyState('W') & 0x8000)
		{
			mSpeed;
			vPos.y -= 0.01f;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			vPos.y += 0.01f;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			vPos.x -= 0.01f;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			vPos.x += 0.01f;
		}



		SetPos(vPos);
	}
}