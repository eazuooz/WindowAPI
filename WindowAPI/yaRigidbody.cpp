#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaObject.h"

namespace ya
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
	{

	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Tick()
	{
		// F = M x A
// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::DeltaTime();

		// �ӵ��� �°� ��ü�� �̵���Ų��.
		Vector2 pos = GetOwner()->GetPos();
		pos += mVelocity * Time::DeltaTime();
		GetOwner()->SetPos(pos);
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{

	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}

}