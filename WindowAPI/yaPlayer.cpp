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
		// Ű�Է¿� ���� �̵�
		Vector2 vPos = GetPos();

		// �ð� ����ȭ
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