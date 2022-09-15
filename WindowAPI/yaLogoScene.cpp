#include "yaLogoScene.h"
#include "yaPlayer.h"

namespace ya
{
	void LogoScene::Initialize()
	{
		Object* player = new Player();
		player->SetPos(Vector2(500.f, 500.f));
		player->SetScale(Vector2(50.f, 50.f));

		AddObject(player);
	}
}
