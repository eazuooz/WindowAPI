#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Component;
	class Object : public Entity
	{
	public:
		Object();
		~Object();

		virtual void Tick();
		virtual void Render(HDC hdc);

		void AddComponent(Component* component);

	public:
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }

	private:
		Vector2 mPos;
		Vector2 mScale;

		std::vector<Component*> mComponents;
	};
}
