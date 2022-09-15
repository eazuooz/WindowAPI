#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Object : public Entity
	{
	public:
		Object();
		~Object();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc);

	public:
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }

	private:
		Vector2 mPos;
		Vector2 mScale;
	};
}
