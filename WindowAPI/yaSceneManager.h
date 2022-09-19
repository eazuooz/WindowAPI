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
		Scene* mScenes[SCENE_TYPE::END];
		Scene* mPlayScene;
	};
}