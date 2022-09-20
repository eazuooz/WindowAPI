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
		DeleteDC(mWindowData.backBuffer);
		DeleteObject(mWindowData.backTexture);

		// �� ������û
		for (UINT i = 0; i < (UINT)PEN_COLOR::END; ++i)
		{
			DeleteObject(mPens[i]);
		}
	}
	
	bool Application::Initialize(WindowData& data)
	{
		if (!InitializeWindow(data))
			return false;

		// �⺻ �� �� �귯�� ����
		createDefaultGDIObject();

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
	void Application::createDefaultGDIObject()
	{
		// ���� �� ������ �� ����
		mPens[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		// ���� �� Brush ����
		mBrushes[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)BRUSH_COLOR::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)BRUSH_COLOR::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
	}
}