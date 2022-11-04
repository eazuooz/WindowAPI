#pragma once
#include "yaEntity.h"

namespace ya
{
	class UIBase : public Entity
	{
	public:
		UIBase(eUIType type);
		virtual ~UIBase();

		/// <summary>
		/// UI가 로드 되었을때 불리는 초기화 함수
		/// </summary>
		void Initialize();
		/// <summary>
		/// UI가 활성화되면 불리는 함수
		/// </summary>
		void Active();
		/// <summary>
		/// UI가 비활성화되면 불리는 함수
		/// </summary>
		void InActive();
		/// <summary>
		/// UI가 업데이트 될떄마다 호출되는 함수
		/// </summary>
		void Tick();
		void Render(HDC hdc);
		/// <summary>
		/// UI가 사라질 떄 호출 되는 함수
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

	private:
		UIBase* mParent;
		eUIType mType;
		bool mIsFullScreen;
		bool mEnabled;

		Vector2 mPos;
		Vector2 mSize;
	};
}
