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
		void Initialize(WindowData data);
		void Tick();

		WindowData& GetWindowData() { return mWindowData; }

	private:
		static int mIsStatic;
		
		WindowData mWindowData;
	};
}
