#include "yaApplication.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInputManager.h"
#include "yaResources.h"

namespace ya
{
	//Application* Application::mInstance = nullptr;
	int Application::mIsStatic = 0;

	Application::Application()
	{
		mWindowData.Clear();
	}

	Application::~Application()
	{
		Resources::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		DeleteDC(mWindowData.backBuffer);
		DeleteObject(mWindowData.backTexture);

		// �� ������û
		for (UINT i = 0; i < (UINT)ePenColor::End; ++i)
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
		HBRUSH hPrevBrush = (HBRUSH)SelectObject(mWindowData.backBuffer, mBrushes[(UINT)eBrushColor::Gray]);
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		SelectObject(mWindowData.backBuffer, hPrevBrush);

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
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		// ���� �� Brush ����
		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = (HBRUSH)GetStockObject(GRAY_BRUSH);
	}
}