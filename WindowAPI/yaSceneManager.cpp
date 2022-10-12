#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaLogoScene.h"

namespace ya
{
	Scene* SceneManager::mScenes[eSceneType::End] = {};
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes[Logo] = new LogoScene();
		mPlayScene = mScenes[Logo];
		mScenes[Logo]->Initialize();
	}

	void SceneManager::Release()
	{
		for (int i = 0; i < eSceneType::End; ++i)
		{
			if (nullptr != mScenes[i])
				delete mScenes[i];
		}
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		mPlayScene->Render(hdc);
	}
	void SceneManager::Destroy()
	{
		mPlayScene->Destroy();
	}
}