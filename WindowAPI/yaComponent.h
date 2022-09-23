#pragma once
#include "yaEntity.h"

namespace ya
{
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc) {}

	private:
		const eComponentType mType;

	};
}
