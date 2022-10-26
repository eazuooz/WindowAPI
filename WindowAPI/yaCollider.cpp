#include "yaCollider.h"

#include "yaObject.h"
#include "yaApplication.h"
#include "yaCamera.h"

namespace ya
{
	Collider::Collider(Collider& other)
		: Component(other)
		, mOffset{ other.mOffset }
		, mScale{ other.mScale }
		, mPos{ other.mPos }
		, mCollisionCount(0)
	{

	}
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mOffset{ Vector2::Zero }
		, mScale{ Vector2::Zero }
		, mPos{ Vector2::Zero }
		, mCollisionCount(0)
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
		GetOwner()->OnCollisionEnter(other);

	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		--mCollisionCount;
		GetOwner()->OnCollisionExit(other);
	}
}