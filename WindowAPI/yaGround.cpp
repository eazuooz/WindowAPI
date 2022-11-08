#include "yaGround.h"
#include "yaCollider.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"

namespace ya
{



	void Ground::Tick()
	{
		Object::Tick();
	}

	void Ground::Render(HDC hdc)
	{
		Object::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		Player* pPlayer = dynamic_cast<Player*>(other->GetOwner());
		if (nullptr == pPlayer || (pPlayer)->IsDead())
			return;

		pPlayer->GetComponent<Rigidbody>()->mbGround = (true);

		float fLen = fabs(pPlayer->GetComponent<Collider>()->GetPos().y - GetComponent<Collider>()->GetPos().y);
		float fScale = (pPlayer->GetComponent<Collider>()->GetScale().y / 2.f) + (GetComponent<Collider>()->GetScale().y / 2.f);

		if (fLen < fScale)
		{
			Vector2 vPlayerPos = pPlayer->GetPos();
			vPlayerPos.y -= (fScale - fLen) - 1.f;
			pPlayer->SetPos(vPlayerPos);
		}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
		Player* pPlayer = dynamic_cast<Player*>(other->GetOwner());
		if (nullptr == pPlayer || (pPlayer)->IsDead())
			return;
	}

	void Ground::OnCollisionExit(Collider* other)
	{
		Player* pPlayer = dynamic_cast<Player*>(other->GetOwner());
		if (nullptr == pPlayer || (pPlayer)->IsDead())
			return;

		pPlayer->GetComponent<Rigidbody>()->mbGround = (false);
	}

	Ground::Ground()
	{
		AddComponent(new Collider);
		GetComponent<Collider>()->SetScale(Vector2(600.f, 50.f));
		
	}

	Ground::~Ground()
	{
	}

}
