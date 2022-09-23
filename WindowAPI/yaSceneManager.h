#pragma once
#include "Common.h"

namespace ya
{
	class Scene;
	class SceneManager
	{
		SINGLE(SceneManager)
	public:
		void Initialize();
		void Tick();
		void Render(HDC hdc);

		Scene* GetPlayScene() { return mPlayScene; }

	private:
		Scene* mScenes[eSceneType::End];
		Scene* mPlayScene;
	};
}