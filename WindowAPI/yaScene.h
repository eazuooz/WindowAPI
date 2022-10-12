#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "yaObject.h"

namespace ya
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize() = 0;
		virtual void Tick();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		void AddObject(Object* object, eColliderLayer type);
		std::vector<std::vector<Object*>>& GetObjects()
		{
			return mObjects;
		}
		std::vector<Object*>& GetObjects(eColliderLayer type)
		{
			return mObjects[(UINT)type];
		}

	private:
		std::vector<std::vector<Object*>> mObjects;
	};

	typedef std::vector<std::vector<Object*>> SceneObjects;
	typedef std::vector<Object*> LayerObjects;

	typedef std::vector<std::vector<Object*>>::iterator SceneObjectsIter;
	typedef std::vector<Object*>::iterator LayerObjectsIter;
}
