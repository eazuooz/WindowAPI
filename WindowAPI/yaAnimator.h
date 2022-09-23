#pragma once
#include "yaComponent.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Tick() override;
	};
}
