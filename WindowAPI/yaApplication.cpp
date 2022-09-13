#include "yaApplication.h"

namespace ya
{
	Application* Application::mInstance = nullptr;
	int Application::mIsStatic = 0;

	Application::Application()
	{
		mWindowData.Clear();
	}

	Application::~Application()
	{
		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
	}
	
	void Application::Initialize(WindowImplData data)
	{
		mWindowData.hWnd = data.hWnd;
		mWindowData.hdc = GetDC(mWindowData.hWnd);
	}

	void Application::Tick()
	{
		// 업데이트
		static float x = 100, y = 100;
		static float sizex = 100, sizey = 100;

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			x -= 0.01f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			x += 0.01f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			y -= 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			y += 0.01f;
		}

		// 렌더링
		Rectangle(mWindowData.hdc
			, (int)(x - sizex / 2.f)
			, (int)(y - sizey / 2.f)
			, (int)(x + sizex / 2.f)
			, (int)(y + sizey / 2.f));
	}
}