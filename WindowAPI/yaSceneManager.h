#pragma once
#include "Common.h"

namespace ya
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Release();
		static void Tick();
		static void Render(HDC hdc);
		static void Destroy();

		static void SceneChange(eSceneType type);
		static inline Scene* GetPlayScene() { return mPlayScene; }
		static eSceneType GetSecneType() { return mSceneType; }

	private:
		SceneManager() = delete;
		~SceneManager() = delete;

	private:
		static Scene* mScenes[eSceneType::End];
		static Scene* mPlayScene;
		static eSceneType mSceneType;
	};
}