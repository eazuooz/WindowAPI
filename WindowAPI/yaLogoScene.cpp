#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"

#include "yaGameObject.h"

namespace ya
{
	void LogoScene::Initialize()
	{
		//Player* pplayer = object::Instantiate<Player>(eColliderLayer::Player);

		Player* player = new Player();
		player->SetPos(Vector2(500.f, 500.f));
		player->SetScale(Vector2(50.f, 50.f));

		AddObject(player, eColliderLayer::Player);

		//gameObject::Instantiate<Player>(Vector2(500.f, 500.f), eColliderLayer::Player);

		//gameObject::Instantiate<Player>(player, eColliderLayer::Player);

		// Monster »ý¼º
		Monster* pMonster = new Monster;
		pMonster->SetPos(Vector2(1920.0f / 2.0f - 100, 1080.0f / 5.0f));
		pMonster->SetScale(Vector2(50.f, 50.f));
		
		AddObject(pMonster, eColliderLayer::Monster);

		gameObject::Instantiate<Monster>(pMonster, eColliderLayer::Monster);

		pMonster->SetPos(Vector2(1920.0f / 2.0f, 1080.0f / 5.0f));
		//Object* pMonster2 = new Monster;
		//pMonster2->SetPos(Vector2(1920.0f / 2.0f - 100, 1080.0f / 5.0f));
		//pMonster2->SetScale(Vector2(50.f, 50.f));

		//AddObject(pMonster2, eColliderLayer::Monster);

		//Camera::PushEffect(eCameraEffect::Fade_In, 2.0f);
		Camera::PushEffect(eCameraEffect::Fade_In, 2.0f);
		

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::MosterProjectile, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::PlayerProjecttile, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster, true);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Monster, true);

	}
}
