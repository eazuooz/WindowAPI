#include "yaCollider.h"

#include "yaObject.h"
#include "yaApplication.h"
#include "yaCamera.h"

namespace ya
{

	Collider::Collider()
		: Component(eComponentType::Collider)
	{

	}

	Collider::~Collider()
	{
		
	}

	void Collider::Tick()
	{
		Object* pOwner = GetOwner();
		mPos = pOwner->GetPos() + mOffset;
	}

	void Collider::Render(HDC hdc)
	{
		assert(0 <= mCollisionCount);

		Pen pen(hdc, Application::GetInstance().GetPen(ePenColor::Green));

		if (0 < mCollisionCount)
			pen.SetColor(Application::GetInstance().GetPen(ePenColor::Red));
		else
			pen.SetColor(Application::GetInstance().GetPen(ePenColor::Green));

		Brush brush(hdc, Application::GetInstance().GetBrush(eBrushColor::Transparent));

		
		Vector2 pos = Camera::CalulatePos(mPos);

		Rectangle(hdc, (int)(pos.x - mScale.x / 2.f)
			, (int)(pos.y - mScale.y / 2.f)
			, (int)(pos.x + mScale.x / 2.f)
			, (int)(pos.y + mScale.y / 2.f));

	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		++mCollisionCount;
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		int a = 0;
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		--mCollisionCount;
	}
}