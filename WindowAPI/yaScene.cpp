#include "yaScene.h"
#include "yaObject.h"
#include "yaGameObject.h"
#include "yaCollisionManager.h"

namespace ya
{
	Scene::Scene()
	{
		mObjects.resize(_COLLIDER_LAYER);
	}

	Scene::~Scene()
	{
		for (size_t y = 0; y < (UINT)eColliderLayer::End; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				if (mObjects[y][x] != nullptr)
					delete mObjects[y][x];
			}
		}

	}

	void Scene::Tick()
	{
		for (size_t y = 0; y < (UINT)eColliderLayer::End; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				if (mObjects[y][x] == nullptr)
					continue;
				if (mObjects[y][x]->IsDead())
					continue;

				mObjects[y][x]->Tick();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (size_t y = 0; y < (UINT)eColliderLayer::End; y++)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				if (mObjects[y][x] == nullptr)
					continue;
				if (mObjects[y][x]->IsDead())
					continue;

				mObjects[y][x]->Render(hdc);
			}
		}
	}

	void Scene::Destroy()
	{
		gameObject::Release();
	}

	void Scene::Enter()
	{

	}

	void Scene::Exit()
	{
		CollisionManager::clear();
	}

	void Scene::AddObject(Object* object, eColliderLayer type)
	{
		mObjects[(UINT)type].push_back(object);
	}
}
