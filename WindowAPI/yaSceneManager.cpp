#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaLogoScene.h"

namespace ya
{
	SceneManager* SceneManager::mInstance = nullptr;
	SceneManager::SceneManager()
		: mScenes{}
		, mPlayScene(nullptr)
	{
	}

	SceneManager::~SceneManager()
	{
		for (int i = 0; i < SCENE_TYPE::END; ++i)
		{
			if (nullptr != mScenes[i])
				delete mScenes[i];
		}
	}

	void SceneManager::Initialize()
	{
		mScenes[LOGO] = new LogoScene();
		mScenes[LOGO]->Initialize();

		mPlayScene = mScenes[LOGO];
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		mPlayScene->Render(hdc);
	}
}