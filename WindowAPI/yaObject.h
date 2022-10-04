#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Collider;
	class Component;
	class Object : public Entity
	{
	public:
		Object();
		~Object();

		virtual void Tick();
		virtual void Render(HDC hdc);

		void AddComponent(Component* component);
	
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }

		inline Collider* GetCollider() 
		{ 
			return (Collider*)(mComponents[(UINT)eComponentType::Collider]); 
		}

	private:
		std::vector<Component*> mComponents;
		Vector2 mPos;
		Vector2 mScale;
	};
}
