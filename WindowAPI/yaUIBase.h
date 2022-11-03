#pragma once
#include "yaEntity.h"

namespace ya
{
	class UIBase : public Entity
	{
	public:
		UIBase(eUIType type);
		~UIBase();

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
		virtual void OnClear();

		eUIType GetType() { return mType; }
		bool GetIsFullScreen() { return mIsFullScreen; }
		void SetIsFullScreen(bool enable) { mIsFullScreen = enable; }

	private:
		eUIType mType;
		bool mIsFullScreen;
		bool mEnabled;
	};
}
