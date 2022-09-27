#pragma once
#include "yaEntity.h"

namespace ya
{
	class Object;
	class Component : public Entity
	{
	public:
		friend class Object;
		Component(eComponentType type);
		~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc) {}

		eComponentType GetType() { return mType; }
		Object* GetOwner() { return mOwner; }

	private:
		const eComponentType mType;
		Object* mOwner;
	};
}
