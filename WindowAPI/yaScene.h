#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Object;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize() = 0;
		virtual void Tick();
		virtual void Render(HDC hdc);

		void AddObject(Object* object);

	private:
		std::vector<Object*> mObjects;
	};
}
