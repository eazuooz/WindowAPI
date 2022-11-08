#pragma once
#include "Common.h"
#include "yaComponent.h"

namespace ya
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody(Rigidbody& other) = default;
		Rigidbody();
		~Rigidbody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }

	public:
		Vector2 mForce;
		Vector2 mVelocity;
		Vector2 mLimitVelocity;

		// ¸¶Âû
		float mMass;
		float mFriction;
		Vector2 mAccelation;
		
		// Áß·Â
		Vector2 mGravity;
		bool mbGround;
	};
}


