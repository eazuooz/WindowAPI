#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaObject.h"

namespace ya
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(10.0f)
	{
		
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Tick()
	{
		// �߷��̵�
		//Vector2 pos = GetOwner()->GetPos();

		//if (pos.y >= 980.0f && mForce.y == 0.0f)
		//{
		//	return;
		//}

		//mGravity = Vector2(0.0f, 9.8f);
		//mVelocity += (mGravity * mMass) * Time::DeltaTime();
		//
		//// F = M x A
		//// A = F / M
		//mAccelation = mForce / mMass;

		//// �ӵ��� ���ӵ��� ���Ѵ�
		//mVelocity += mAccelation * Time::DeltaTime();

		//// �ӵ��� �°� ��ü�� �̵���Ų��.
		//pos += mVelocity;

		//GetOwner()->SetPos(pos);
		//mForce.clear();

		//�̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::DeltaTime();

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		if ( !(mVelocity == Vector2::Zero) )
		{
			
			// �ӵ��� �ݴ� �������� �������� ����
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = Vector2(0.f, 0.f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity += friction;
			}
		}

		// �ӵ��� �°� ��ü�� �̵���Ų��.
		Vector2 pos = GetOwner()->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();
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