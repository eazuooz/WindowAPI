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

		// �ʱ�ȭ
		SceneManager::GetInstance().Initialize();
		Time::GetInstance().Initialize();
	}

	void Application::Tick()
	{
		// ������Ʈ
		Time::GetInstance().Tick();
		SceneManager::GetInstance().Tick();

		// ������
		SceneManager::GetInstance().Render(mWindowData.hdc);
		Time::GetInstance().Render(mWindowData.hdc);
	}
}