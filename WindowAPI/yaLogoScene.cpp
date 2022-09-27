#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaMonster.h"

namespace ya
{
	void LogoScene::Initialize()
	{
		Object* player = new Player();
		player->SetPos(Vector2(500.f, 500.f));
		player->SetScale(Vector2(50.f, 50.f));

		AddObject(player, eColliderLayer::PLAYER);

		// Monster »ý¼º
		Object* pMonster = new Monster;
		pMonster->SetPos(Vector2(1920.0f / 2.0f, 1080.0f / 5.0f));
		pMonster->SetScale(Vector2(50.f, 50.f));
		
		AddObject(pMonster, eColliderLayer::MONSTER);
	}
}
