#pragma once
#include "yaEntity.h"

namespace ya
{
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};

		UIBase(eUIType type);
		virtual ~UIBase();

		/// <summary>
		/// UI�� �ε� �Ǿ����� �Ҹ��� �ʱ�ȭ �Լ�
		/// </summary>
		void Initialize();
		/// <summary>
		/// UI�� Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		/// </summary>
		void Active();
		/// <summary>
		/// UI�� ��Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		/// </summary>
		void InActive();
		/// <summary>
		/// UI�� ������Ʈ �ɋ����� ȣ��Ǵ� �Լ�
		/// </summary>
		void Tick();
		void Render(HDC hdc);
		/// <summary>
		/// UI�� ����� �� ȣ�� �Ǵ� �Լ�
		/// </summary>
		void UIClear();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnTick();
		virtual void OnRender(HDC hdc);
		virtual void OnClear();

		eUIType GetType() { return mType; }
		bool GetIsFullScreen() { return mIsFullScreen; }
		void SetIsFullScreen(bool enable) { mIsFullScreen = enable; }
		void SetParent(UIBase* parent) { mParent = parent; }
		Vector2 GetPos() { return mPos; }
		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }

		void AddUIBase(UIBase* uiBase);

	protected:
		std::vector<UIBase*> mChilds;
		bool mbMouseOn;
		UIBase* mParent;
		Vector2 mRenderPos;

	private:
		eUIType mType;
		bool mIsFullScreen;
		bool mEnabled;
		Vector2 mPos;
		Vector2 mSize;
	};
}
