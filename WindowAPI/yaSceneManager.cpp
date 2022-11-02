#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaLogoScene.h"
#include "yaToolScene.h"


namespace ya
{
	Scene* SceneManager::mScenes[eSceneType::End] = {};
	Scene* SceneManager::mPlayScene = nullptr;
	eSceneType SceneManager::mSceneType = eSceneType::Logo;

	void SceneManager::Initialize()
	{
		mScenes[Logo] = new LogoScene();
		SceneManager::SceneChange(Logo);
		
		mScenes[Logo]->Initialize();

		mScenes[Tool] = new ToolScene();
		SceneManager::SceneChange(Tool);
		mScenes[Tool]->Initialize();
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
	void SceneManager::SceneChange(eSceneType type)
	{
		if (nullptr != mPlayScene)
		{
			mPlayScene->Exit();
		}

		mPlayScene = mScenes[type];
		mSceneType = type;

		mPlayScene->Enter();
	}
}