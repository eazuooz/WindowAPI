#pragma once
#include "Common.h"
// �츮�� ���� ���α׷�
// Singleton patten

namespace ya
{
	class Application
	{
		SINGLE(Application)
	public:
		void Initialize(WindowImplData data);
		void Tick();

	private:
		static int mIsStatic;
		
		WindowImplData mWindowData;
	};
}
