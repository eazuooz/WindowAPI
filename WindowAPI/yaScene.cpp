#include "yaScene.h"
#include "yaObject.h"

namespace ya
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			delete mObjects[i];
		}
	}

	void Scene::Tick()
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->Tick();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->Render(hdc);
		}
	}

	void Scene::AddObject(Object* object)
	{
		mObjects.push_back(object);
	}
}
