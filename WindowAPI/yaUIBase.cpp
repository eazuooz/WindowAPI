#include "yaUIBase.h"
#include "yaInputManager.h"


namespace ya
{
	UIBase::UIBase(eUIType type)
		: mParent(nullptr)
		, mType(type)
		, mIsFullScreen(false)
		, mEnabled(false)
		, mPos(Vector2::Zero)
		, mSize(Vector2::One)
		, mbMouseOn(false)
	{

	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInit();
		for (UIBase* child : mChilds)
		{
			child->OnInit();
		}
	}

	void UIBase::Active()
	{
		mEnabled = true;
		OnActive();

		for (UIBase* child : mChilds)
		{
			child->Active();
		}
	}

	void UIBase::InActive()
	{
		mEnabled = false;

		for (UIBase* child : mChilds)
		{
			child->InActive();
		}
		OnInActive();
	}

	void UIBase::Tick()
	{
		if (mEnabled == false)
			return;

		OnTick();

		mRenderPos = GetPos();
		if (mParent)
		{
			mRenderPos += mParent->GetPos();
		}

		for (UIBase* child : mChilds)
		{
			if (child->mEnabled)
				child->Tick();
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (mEnabled == false)
			return;

		OnRender(hdc);
		for (UIBase* child : mChilds)
		{
			if (child->mEnabled)
				child->Render(hdc);
		}
	}

	void UIBase::UIClear()
	{
		for (UIBase* child : mChilds)
		{
			child->UIClear();
		}
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

	void UIBase::AddUIBase(UIBase* uiBase)
	{
		mChilds.push_back(uiBase);
		uiBase->SetParent(this);
	}
}
