#include "yaMonster.h"
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

#include "yaMissile.h"

namespace ya
{
	Monster::Monster()
	{
		AddComponent(new Collider());
		AddComponent(new Animator());

		GetCollider()->SetScale(Vector2(200.f, 100.f));
		GetCollider()->SetOffset(Vector2(0.f, 0.f));
	}

	Monster::~Monster()
	{

	}

	void Monster::Tick()
	{
		Object::Tick();
	}

	void Monster::Render(HDC hdc)
	{
		Image* pImage = Resources::Load<Image>(L"MonsterImage", L"..\\Resources\\Images\\Monster.bmp");
		//Image* pImage = Resources::Find<Image>(L"PlayerImage");

		if (nullptr == pImage)
			return;

		Vector2 vPos = GetPos();
		vPos = Camera::CalulatePos(vPos);
		//BitBlt(hdc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetDC(), 0, 0, SRCCOPY);
		TransparentBlt(hdc, (int)vPos.x - pImage->GetWidth() / 2
			, (int)vPos.y - pImage->GetHeight() / 2
			, pImage->GetWidth(), pImage->GetHeight()
			, pImage->GetDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));

		//Resource* p = pImage;

		//delete p;

		Object::Render(hdc);
	}
}
