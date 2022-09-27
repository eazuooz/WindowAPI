#include "yaCollider.h"

#include "yaObject.h"
#include "yaApplication.h"

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
		Pen pen(hdc, Application::GetInstance().GetPen(ePenColor::Green));
		Brush brush(hdc, Application::GetInstance().GetBrush(eBrushColor::Transparent));

		Rectangle(hdc, (int)(mPos.x - mScale.x / 2.f)
			, (int)(mPos.y - mScale.y / 2.f)
			, (int)(mPos.x + mScale.x / 2.f)
			, (int)(mPos.y + mScale.y / 2.f));
	}
}