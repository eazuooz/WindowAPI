#include "yaUIBase.h"



namespace ya
{
	UIBase::UIBase(eUIType type)
		: mParent(nullptr)
		, mType(type)
		, mIsFullScreen(false)
		, mEnabled(false)
		, mPos(Vector2::Zero)
		, mSize(Vector2::One)
	{

	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInit();
	}

	void UIBase::Active()
	{
		mEnabled = true;
		OnActive();
	}

	void UIBase::InActive()
	{
		mEnabled = false;
		OnInActive();
	}

	void UIBase::Tick()
	{
		if (mEnabled == false)
			return;

		OnTick();
	}

	void UIBase::Render(HDC hdc)
	{
		if (mEnabled == false)
			return;

		OnRender(hdc);
	}

	void UIBase::UIClear()
	{
		OnClear();
	}

	void UIBase::OnInit()
	{

	}

	void UIBase::OnActive()
	{

	}

	void UIBase::OnInActive()
	{

	}

	void UIBase::OnTick()
	{

	}

	void UIBase::OnRender(HDC hdc)
	{

	}

	void UIBase::OnClear()
	{

	}
}
