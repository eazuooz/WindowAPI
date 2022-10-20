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

		// 속도에 가속도를 더한다
		mVelocity += mAccelation * Time::DeltaTime();

		// 속도에 맞게 물체를 이동시킨다.
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