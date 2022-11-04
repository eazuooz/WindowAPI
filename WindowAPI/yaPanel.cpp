#include "yaPanel.h"

namespace ya
{
	Panel::Panel(eUIType type)
		: UIBase(type)
	{
	}
	Panel::~Panel()
	{
	}

	void Panel::OnInit()
	{

	}
	
	void Panel::OnActive()
	{

	}
	
	void Panel::OnInActive()
	{

	}
	
	void Panel::OnTick()
	{
		for (UIBase* uiBase : mChilds)
		{
			uiBase->Tick();
		}
	}
	
	void Panel::OnRender(HDC hdc)
	{
		for (UIBase* uiBase : mChilds)
		{
			uiBase->OnRender(hdc);
		}
	}
	
	void Panel::OnClear()
	{
		for (UIBase* uiBase : mChilds)
		{
			uiBase->OnClear();
		}
	}
	
	void Panel::AddUIBase(UIBase* uiBase)
	{
		mChilds.push_back(uiBase);
		uiBase->SetParent(this);
	}
}
