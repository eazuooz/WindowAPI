#include "yaUIManager.h"



namespace ya
{
	std::unordered_map< eUIType, UIBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIBases;
	UIBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{
		UIBase* p = new UIBase(eUIType::HP);
		mUIs.insert(std::make_pair(eUIType::HP, p));
		p = new UIBase(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, p));
		p = new UIBase(eUIType::SHOP);
		p->SetIsFullScreen(true);
		mUIs.insert(std::make_pair(eUIType::SHOP, p));
		p = new UIBase(eUIType::INVENTORY);
		mUIs.insert(std::make_pair(eUIType::INVENTORY, p));
		p = new UIBase(eUIType::OPTION);
		p->SetIsFullScreen(true);
		mUIs.insert(std::make_pair(eUIType::OPTION, p));
	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map< eUIType, UIBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
		/// 정의된 UI 데이터로 부터 추가할 UI 데이터를 얻은 후 리소스 매니저를 통해 로드 

		// 제대로 로드가 되었다면 Oncomplete

		// 그렇지 않다면 fail
	}

	void UIManager::Tick()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();

			if (uiBase != nullptr)
			{
				uiBase->Tick();
				uiBases.pop();
			}
		}

		if (mRequestUIQueue.size() > 0)
		{
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUI);
		}
	}

	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();

			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
				uiBases.pop();
			}
		}
	}

	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		// 만약에 현재 추가된 UI 가 전체화면이라면
		// 전체 화면인 ui 비활성화 해줘야한다.
		if (addUI->GetIsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase->GetIsFullScreen())
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
		mCurrentData = nullptr;
	}

	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UIBase*> tempStack;

		UIBase* uiBase;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			// pop 하는 ui가 전체화면일 경우, 남은 ui 중 전체화면인 가장 상단의 ui를 활성화
			if (uiBase->GetType() == type)
			{
				if (uiBase->GetIsFullScreen())
				{
					std::stack<UIBase*> uiBases = mUIBases;
					while (!mUIBases.empty())
					{
						UIBase* uiBase = uiBases.top();
						uiBases.pop();
						if (uiBase->GetIsFullScreen())
						{
							uiBase->Active();
							break;
						}
					}
				}

				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}
		}

		while (tempStack.size() > 0)
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}
	}
}
