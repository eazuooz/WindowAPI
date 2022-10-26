#pragma once
#include "Common.h"
#include "yaComponent.h"
#include "yaEntity.h"


namespace ya
{
	class Collider;
	class Object : public Entity
	{
	public:
		Object(Object& other);
		Object();
		~Object();

		virtual void Tick();
		virtual void Render(HDC hdc);

		Component* CreateComponent(Component* component);
		void AddComponent(Component* component);
	
		virtual void OnCollisionEnter(Collider* other) {};
		virtual void OnCollisionStay(Collider* other) {};
		virtual void OnCollisionExit(Collider* other) {};
		
		template <typename T>
		__forceinline T* GetComponent()
		{
			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);
				if (component != nullptr)
				{
					return component;
				}
			}
			return nullptr;
		}
		__forceinline Component* GetComponentOfType(eComponentType type)
		{
			Component* comp = nullptr;
			for (Component* c : mComponents)
			{
				if (c->GetType() == type)
				{
					comp = c;
					break;
				}
			}
			return comp;
		}

		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }
		bool IsDead() { return mbDead; }
		void Death() { mbDead = true; }

	private:
		std::vector<Component*> mComponents;
		Vector2 mPos;
		Vector2 mScale;
		bool mbDead;
	};
}
