#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Image;
	class Button : public UIBase
	{
	public:
		Button(eUIType type);
		virtual ~Button();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;
		
		virtual void Click();

	private:
		Image* mImage;
		Event mOnClick;
	};
}
