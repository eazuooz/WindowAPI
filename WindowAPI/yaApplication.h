#pragma once
#include "Common.h"
// 우리의 메인 프로그램
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
