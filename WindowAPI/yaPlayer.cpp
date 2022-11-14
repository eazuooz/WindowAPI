#include "yaPlayer.h"

#include "yaTime.h"
#include "yaInputManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaImage.h"

#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaCamera.h"
#include "yaRigidbody.h"

#include "yaMissile.h"
#include "yaUIManager.h"

namespace ya
{
	Player::Player()
		: mSpeed(100.0f)
		, mShotTime(0.0f)
	{
		AddComponent(new Collider());
		AddComponent(new Animator());
		AddComponent(new Rigidbody());

		GetComponent<Collider>()->SetScale(Vector2(50.0f, 50.0f));
		GetComponent<Collider>()->SetOffset(Vector2(0.0f, 25.0f));

		Image* pImage
			= Resources::Load<Image>(L"PlayerImage", L"..\\Resources\\Images\\link.bmp");
		
		Animator* animator = GetComponent<Animator>();
		animator->CreateAnimaiton(L"Walk_Up", pImage, Vector2(0.f, 780.f), Vector2(120.f, 130.f), Vector2(0.f, -30.f), 120.f, 10, 0.1f);
		animator->CreateAnimaiton(L"Walk_Down", pImage, Vector2(0.f, 520.f), Vector2(120.f, 130.f), Vector2(0.f, -30.f), 120.f, 10, 0.1f);
		animator->CreateAnimaiton(L"Walk_Left", pImage, Vector2(0.f, 650.f), Vector2(120.f, 130.f), Vector2(0.f, -30.f), 120.f, 10, 0.1f);
		animator->CreateAnimaiton(L"Walk_Right", pImage, Vector2(0.f, 910.f), Vector2(120.f, 130.f), Vector2(0.f, -30.f), 120.f, 10, 0.1f);

		animator->FindEvents(L"Walk_Up")->mCompleteEvent = std::bind(&Player::AnimationStart, this);
		animator->Play(L"Walk_Down", true);


		spriteSheet = Image::Create(L"SPRITETEST", 123 * 2, 124);
		
		//123 * 2 , 124
		//Image* pImage2
		//	= Resources::Load<Image>(L"TestBLT", L"..\\Resources\\Images\\Fighter.bmp");

		//BitBlt(spriteSheet->GetHdc(), 0,0, 123, 124, pImage2->GetHdc(), 0,0, SRCCOPY);
		//BitBlt(spriteSheet->GetHdc(), 123, 0, 123, 124, pImage2->GetHdc(), 0, 0, SRCCOPY);

	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		// 키입력에 따른 이동
		Vector2 vPos = GetPos();

		// 시간 동기화
		if (KEY_PREESED(KEY_CODE::W))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}

		if (KEY_PREESED(KEY_CODE::S))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}

		if (KEY_PREESED(KEY_CODE::A))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}

		if (KEY_PREESED(KEY_CODE::D))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}

		if (KEY_DOWN(KEY_CODE::W))
			GetComponent<Animator>()->Play(L"Walk_Up", true);
		if (KEY_DOWN(KEY_CODE::S))
			GetComponent<Animator>()->Play(L"Walk_Down", true);
		if (KEY_DOWN(KEY_CODE::A))
			GetComponent<Animator>()->Play(L"Walk_Left", true);
		if (KEY_DOWN(KEY_CODE::D))
			GetComponent<Animator>()->Play(L"Walk_Right", true);


		if (KEY_DOWN(KEY_CODE::SPACE))
		{
			Vector2 vV = GetComponent<Rigidbody>()->mVelocity;
			vV.y = -500.f;
			GetComponent<Rigidbody>()->mVelocity = (vV);
			GetComponent<Rigidbody>()->mbGround = (false);

			//UIManager::Pop(eUIType::OPTION);
			//if (mShotTime >= 0.1f)
			//{
			//	//Missile* misile = Instantiate<Missile>();

			//	// 미사일 쏘기
			//	Scene* pCurScene = SceneManager::GetPlayScene();
			//	Missile* pMissile = new Missile();

			//	pMissile->SetPos(GetPos());
			//	pMissile->SetScale(Vector2(20.f, 20.f));

			//	pCurScene->AddObject(pMissile, eColliderLayer::PlayerProjecttile);

			//	mShotTime = 0.f;
			//}
		}
		mShotTime += Time::DeltaTime();

		SetPos(vPos);
		Object::Tick();
	}

	void Player::Render(HDC hdc)
	{
		//Image* pImage 
		//	= Resources::Load<Image>(L"PlayerImage", L"..\\Resources\\Images\\Fighter.bmp");
		//if (nullptr == pImage)
		//	return;

		//Vector2 vPos = GetPos();
		//vPos = Camera::CalulatePos(vPos);
		//TransparentBlt(hdc, (int)vPos.x - spriteSheet->GetWidth() / 2
		//	, (int)vPos.y - spriteSheet->GetHeight() / 2
		//	, spriteSheet->GetWidth(), spriteSheet->GetHeight()
		//	, spriteSheet->GetHdc(), 0, 0, spriteSheet->GetWidth(), spriteSheet->GetHeight(), RGB(255, 0, 255));

		Object::Render(hdc);
	}
}