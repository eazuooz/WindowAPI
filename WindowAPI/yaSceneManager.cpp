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
		for (int i = 0; i < eSceneType::End; ++i)
		{
			if (nullptr != mScenes[i])
				delete mScenes[i];
		}
	}

	void SceneManager::Initialize()
	{
		mScenes[Logo] = new LogoScene();
		mScenes[Logo]->Initialize();

		mPlayScene = mScenes[Logo];
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