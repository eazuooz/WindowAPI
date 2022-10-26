#pragma once
#include "yaComponent.h"

namespace ya
{

	class Collider : public Component
	{
	public:
		Collider(Collider& other);
		Collider();
		~Collider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		Vector2 GetScale() { return mScale; }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetOffset(Vector2 offset) { mOffset = offset; }

	private:
		Vector2 mOffset;
		Vector2 mScale;
		Vector2 mPos;
		UINT mCollisionCount;
	};

}
