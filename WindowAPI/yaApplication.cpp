#include "yaApplication.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInputManager.h"

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
	
	bool Application::Initialize(WindowData& data)
	{
		if (!InitializeWindow(data))
			return false;

		// �ʱ�ȭ
		SceneManager::GetInstance().Initialize();
		Time::GetInstance().Initialize();
		InputManager::GetInstance().Initialize();

		return true;
	}

	bool Application::InitializeWindow(WindowData& data)
	{
		mWindowData.hWnd = data.hWnd;
		mWindowData.hdc = GetDC(mWindowData.hWnd);
		mWindowData.width = data.width;
		mWindowData.height = data.height;


		// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ������ ũ�� ���� �� ��� ����
		SetWindowPos(mWindowData.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mWindowData.hWnd, true);

		// ���� ���۸�
		// ������ �ػ󵵿� ������ ũ���� ��Ʈ���� ����
		// ���� ������ ��Ʈ���� ����Ű�� ���� DC ����
		// ���� ������ ��Ʈ�ʰ� DC �� ���� ����
		mWindowData.backTexture
			= CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);
		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);
		DeleteObject(defaultBitmap);

		return true;
	}

	void Application::Tick()
	{
		// ������Ʈ
		Time::GetInstance().Tick();
		InputManager::GetInstance().Tick();
		SceneManager::GetInstance().Tick();

		
		// Clear
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);

		// ������
		SceneManager::GetInstance().Render(mWindowData.backBuffer);
		Time::GetInstance().Render(mWindowData.backBuffer);

		// BitBlt �Լ��� DC ���� �׸��� �����ϴ� �Լ��Դϴ�. 
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height
			, mWindowData.backBuffer, 0, 0, SRCCOPY);
	}
}