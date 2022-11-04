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
		/// ���ǵ� UI �����ͷ� ���� �߰��� UI �����͸� ���� �� ���ҽ� �Ŵ����� ���� �ε� 

		// ����� �ε尡 �Ǿ��ٸ� Oncomplete

		// �׷��� �ʴٸ� fail
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

		// ���࿡ ���� �߰��� UI �� ��üȭ���̶��
		// ��ü ȭ���� ui ��Ȱ��ȭ ������Ѵ�.
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

			// pop �ϴ� ui�� ��üȭ���� ���, ���� ui �� ��üȭ���� ���� ����� ui�� Ȱ��ȭ
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
