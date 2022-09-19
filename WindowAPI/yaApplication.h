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
		bool Initialize(WindowData& data);
		bool InitializeWindow(WindowData& data);
		void Tick();

		WindowData& GetWindowData() { return mWindowData; }

	private:
		static int mIsStatic;
		
		WindowData mWindowData;
	};
}
