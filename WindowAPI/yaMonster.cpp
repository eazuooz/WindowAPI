#include "yaMonster.h"
#include "yaTime.h"
#include "yaInputManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaGameObject.h"

#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaCamera.h"

#include "yaMissile.h"
#include "yaUIManager.h"

namespace ya
{
	Monster::Monster()
		: mImage(nullptr)
	{
		AddComponent(new Collider());
		AddComponent(new Animator());

		GetComponent<Collider>()->SetScale(Vector2(200.f, 100.f));
		GetComponent<Collider>()->SetOffset(Vector2(0.f, 0.f));

		mImage = Resources::Load<Image>(L"MonsterImage", L"..\\Resources\\Images\\Monster.bmp");
	}

	Monster::~Monster()
	{

	}

	void Monster::Tick()
	{
		Object::Tick();

		//UIManager::Pop(eUIType::OPTION);
	}

	void Monster::Render(HDC hdc)
	{
		if (nullptr == mImage)
			return;

		Vector2 vPos = GetPos();
		vPos = Camera::CalulatePos(vPos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 127;
		
		AlphaBlend(hdc, (int)vPos.x - mImage->GetWidth() / 2
			, (int)vPos.y - mImage->GetHeight() / 2
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

		Object::Render(hdc);
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
		if (dynamic_cast<Missile*>(other->GetOwner()))
		{
			gameObject::Destroy(this);
		}
	}
	void Monster::OnCollisionStay(Collider* other)
	{

	}
	void Monster::OnCollisionExit(Collider* other)
	{

	}
}
