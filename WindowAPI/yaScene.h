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

		void AddObject(Object* object, eColliderLayer type);
		const std::vector<Object*>& GetObjects(eColliderLayer type)
		{
			return mObjects[(UINT)type];
		}

	private:
		std::vector<std::vector<Object*>> mObjects;
	};
}
