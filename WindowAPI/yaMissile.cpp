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

		GetComponent<Collider>()->SetScale(Vector2(20.f, 20.f));
		GetComponent<Collider>()->SetOffset(Vector2(0.f, 0.f));

		//Camera::SetTarget(this);
		m_vDir = Vector2(0.0f, 1.0f);
	}

	Missile::~Missile()
	{

	}

	void Missile::Tick()
	{
		Vector2 vPos = GetPos();
		//vPos.y -= m_fSpeed * Time::DeltaTime();

		//vPos.x += m_fSpeed * cosf(m_fDir) * DT;
		//vPos.y -= m_fSpeed * sinf(m_fDir) * DT;

		//pMissile->SetDir(PI / 4.f);
		//m_vDir = Vector2(0.0f, 1.0f);
		m_vDir = ya::math::Rotate(m_vDir, 1.0f);


		vPos.x += m_fSpeed * m_vDir.x * Time::DeltaTime();
		vPos.y += m_fSpeed * m_vDir.y * Time::DeltaTime();


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
			, pImage->GetHdc(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));

		Object::Render(hdc);
	}
}