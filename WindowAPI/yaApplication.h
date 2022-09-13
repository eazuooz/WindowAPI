#pragma once
#include "Common.h"
// 우리의 메인 프로그램
// Singleton patten

namespace ya
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new Application();
			}
			return *mInstance;
		}

		Application();
		~Application();

		void Initialize(WindowImplData data);
		void Tick();

	private:
		static Application* mInstance;
		static int mIsStatic;
		
		WindowImplData mWindowData;
	};
}
