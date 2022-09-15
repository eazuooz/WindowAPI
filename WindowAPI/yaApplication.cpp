#include "yaApplication.h"
#include "yaTime.h"
#include "yaSceneManager.h"

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

		// 초기화
		SceneManager::GetInstance().Initialize();
		Time::GetInstance().Initialize();
	}

	void Application::Tick()
	{
		// 업데이트
		Time::GetInstance().Tick();
		SceneManager::GetInstance().Tick();

		// 렌더링
		SceneManager::GetInstance().Render(mWindowData.hdc);
		Time::GetInstance().Render(mWindowData.hdc);
	}
}