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
		// Ű�Է¿� ���� �̵�
		Vector2 vPos = GetPos();


		// �ð� ����ȭ
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