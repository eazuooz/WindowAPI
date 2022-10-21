#pragma once
#include "Common.h"
#include "yaComponent.h"

namespace ya
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }

	private:
		float mMass;
		
		float mFriction;
		float mStaticFriction;
		float mKineticFriction;
		float mCoefficientFriction;
		
		float mNormalForce;

		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mGravity;
	};
}


