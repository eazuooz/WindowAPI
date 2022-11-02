#pragma once
#include "yaScene.h"

namespace ya
{
	class LogoScene : public Scene
	{
	public:
		void Initialize() override;

		virtual void Enter() override;
		virtual void Exit() override;
	};
}
