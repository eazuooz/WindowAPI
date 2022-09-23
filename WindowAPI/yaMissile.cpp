#include "yaMissile.h"
#include "yaTime.h"
#include "yaApplication.h"

namespace ya
{

	Missile::Missile()
		: m_fSpeed(400.f)
	{
	}

	Missile::~Missile()
	{

	}

	void Missile::Tick()
	{
		Vector2 vPos = GetPos();

		vPos.y -= m_fSpeed * Time::DeltaTime();

		SetPos(vPos);
	}

	void Missile::Render(HDC _dc)
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();

		Brush b(_dc, Application::GetInstance().GetBrush(eBrushColor::Gray));
		Pen p(_dc, Application::GetInstance().GetPen(ePenColor::Red));

		Ellipse(_dc
			, (int)vPos.x - vScale.x / 2.f
			, (int)vPos.y - vScale.y / 2.f
			, (int)vPos.x + vScale.x / 2.f
			, (int)vPos.y + vScale.y / 2.f);
	}
}