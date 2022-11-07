#include "yaPanel.h"
#include "yaInputManager.h"

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
		SetPos(Vector2(400.0f, 400.0f));
	}
	
	void Panel::OnActive()
	{

	}
	
	void Panel::OnInActive()
	{
		
	}
	
	void Panel::OnTick()
	{
		Vector2 mousePos = InputManager::GetMousPosition();
		Vector2 size = GetSize();
		Vector2 pos = GetPos();

		//for (UIBase* uiBase : mChilds)
		//{
		//	uiBase->Tick();
		//}
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
	

}
