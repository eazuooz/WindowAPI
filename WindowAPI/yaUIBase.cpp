#include "yaUIBase.h"



namespace ya
{
	UIBase::UIBase(eUIType type)
		: mType(type)
		, mIsFullScreen(false)
		, mEnabled(false)
	{

	}
	UIBase::~UIBase()
	{
	}
	void UIBase::Initialize()
	{
	}
	void UIBase::Active()
	{
	}
	void UIBase::InActive()
	{
	}
	void UIBase::Tick()
	{
	}
	void UIBase::Render(HDC hdc)
	{
	}
	void UIBase::UIClear()
	{
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
	void UIBase::OnClear()
	{
	}
}
