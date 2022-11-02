#include "yaApplication.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInputManager.h"
#include "yaResources.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaImage.h"

namespace ya
{
	//Application* Application::mInstance = nullptr;
	int Application::mIsStatic = 0;

	Application::Application()
	{
		mWindow.Clear();
	}

	Application::~Application()
	{
		Resources::Release();
		SceneManager::Release();

		ReleaseDC(mWindow.hWnd, mWindow.hdc);
		DeleteDC(mWindow.backBuffer);
		DeleteObject(mWindow.backTexture);

		// 펜 삭제요청
		for (UINT i = 0; i < (UINT)ePenColor::End; ++i)
		{
			DeleteObject(mPens[i]);
		}

		DestroyMenu(mMenuBar);
	}
	
	bool Application::Initialize(WindowData& data)
	{
		if (!InitializeWindow(data))
			return false;

		// 기본 펜 및 브러쉬 생성
		createDefaultGDIObject();

		// 초기화
		SceneManager::Initialize();
		Time::Initialize();
		InputManager::Initialize();
		Camera::Initialize();

		return true;
	}

	bool Application::InitializeWindow(WindowData& data)
	{
		mWindow.hWnd = data.hWnd;
		mWindow.hdc = GetDC(mWindow.hWnd);
		mWindow.width = data.width;
		mWindow.height = data.height;

		RECT rect = { 0, 0, mWindow.width, mWindow.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mWindow.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mWindow.hWnd, true);

		Image* backHdc 
			= Image::Create(L"BackBuffer", mWindow.width, mWindow.height);
		mWindow.backTexture = backHdc->GetHBitmap();
		mWindow.backBuffer = backHdc->GetHdc();

		mMenuBar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_WINDOWAPI));

		return true;
	}

	void Application::Tick()
	{
		// 업데이트
		Time::Tick();
		InputManager::Tick();
		Camera::Tick();

		SceneManager::Tick();
		CollisionManager::Tick();
		
		// Clear
		HBRUSH hPrevBrush = (HBRUSH)SelectObject(mWindow.backBuffer, mBrushes[(UINT)eBrushColor::Gray]);
		Rectangle(mWindow.backBuffer, -1, -1, mWindow.width + 1, mWindow.height + 1);
		SelectObject(mWindow.backBuffer, hPrevBrush);

		// 렌더링
		SceneManager::Render(mWindow.backBuffer);
		Time::Render(mWindow.backBuffer);
		Camera::Render(mWindow.backBuffer);

		// BitBlt 함수는 DC 간에 그림을 복사하는 함수입니다. 
		BitBlt(mWindow.hdc, 0, 0, mWindow.width, mWindow.height
			, mWindow.backBuffer, 0, 0, SRCCOPY);

		// 파괴
		SceneManager::Destroy();
	}

	void Application::SetMenuBar(bool power)
	{
		SetMenu(mWindow.hWnd, mMenuBar);

		RECT rect = { 0, 0, mWindow.width, mWindow.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);
		SetWindowPos(mWindow.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mWindow.hWnd, true);
	}

	void Application::createDefaultGDIObject()
	{
		// 자주 쓸 색상의 펜 생성
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

		// 자주 쓸 Brush 생성
		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = (HBRUSH)GetStockObject(GRAY_BRUSH);
	}
}