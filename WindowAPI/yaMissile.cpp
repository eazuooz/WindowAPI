#include "yaMissile.h"
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


namespace ya
{

	Missile::Missile()
		: m_fSpeed(400.f)
	{
		AddComponent(new Collider());
		//AddComponent(new Animator());

		GetCollider()->SetScale(Vector2(20.f, 20.f));
		GetCollider()->SetOffset(Vector2(0.f, 0.f));

		Camera::SetTarget(this);
	}

	Missile::~Missile()
	{

	}

	void Missile::Tick()
	{
		Vector2 vPos = GetPos();
		vPos.y -= m_fSpeed * Time::DeltaTime();
		SetPos(vPos);

		Object::Tick();
	}

	void Missile::Render(HDC hdc)
	{
		Image* pImage = Resources::Load<Image>(L"BulletImage", L"..\\Resources\\Images\\missile.bmp");

		if (nullptr == pImage)
			return;

		Vector2 vPos = GetPos();
		vPos = Camera::CalulatePos(vPos);
		
		TransparentBlt(hdc, (int)vPos.x - pImage->GetWidth() / 2
			, (int)vPos.y - pImage->GetHeight() / 2
			, pImage->GetWidth(), pImage->GetHeight()
			, pImage->GetDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));

		Object::Render(hdc);
	}
}