#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Image;
	class HUD : public UIBase
	{
	public:
		HUD(eUIType type);
		~HUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
		Image* mImage;
	};
}
