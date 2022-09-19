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
		bool Initialize(WindowData& data);
		bool InitializeWindow(WindowData& data);
		void Tick();

		WindowData& GetWindowData() { return mWindowData; }

	private:
		static int mIsStatic;
		
		WindowData mWindowData;
	};
}
