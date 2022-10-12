#pragma once
#include "yaScene.h"
#include "yaObject.h"
#include "yaSceneManager.h"


namespace ya
{
	namespace gameObject
	{
		template <typename T>
		static __forceinline T* Instantiate(Vector2 position, eColliderLayer type)
		{
			T* gameObject = new T(position);
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddObject(dynamic_cast<Object*>(gameObject), type);

			return gameObject;
		}
		template <typename T>
		static __forceinline T* Instantiate(eColliderLayer type)
		{
			T* gameObject = new T();
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddObject(dynamic_cast<Object*>(gameObject), type);

			return gameObject;
		}

		static __forceinline void Destroy(Object* object)
		{
			object->Death();
		}

		static __forceinline void Release()
		{
			Scene* scene = SceneManager::GetPlayScene();
			SceneObjects objects = scene->GetObjects();

			for (size_t y = 0; y < _COLLIDER_LAYER; y++)
			{
				for (LayerObjectsIter iter = objects[y].begin()
					; iter != objects[y].end();)
				{
					if ((*iter)->IsDead() == true)
					{
						iter = objects[y].erase(iter);
						continue;
					}
					
					++iter;
				}
			}
		}
	}
}