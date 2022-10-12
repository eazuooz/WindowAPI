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
		mWindowData.Clear();
	}

	Application::~Application()
	{
		Resources::Release();
		SceneManager::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		DeleteDC(mWindowData.backBuffer);
		DeleteObject(mWindowData.backTexture);

		// 펜 삭제요청
		for (UINT i = 0; i < (UINT)ePenColor::End; ++i)
		{
			DeleteObject(mPens[i]);
		}
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
		mWindowData.hWnd = data.hWnd;
		mWindowData.hdc = GetDC(mWindowData.hWnd);
		mWindowData.width = data.width;
		mWindowData.height = data.height;

		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mWindowData.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mWindowData.hWnd, true);

		Image* backHdc 
			= Image::Create(L"BackBuffer", mWindowData.width, mWindowData.height);
		mWindowData.backTexture = backHdc->GetHBitmap();
		mWindowData.backBuffer = backHdc->GetHdc();

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
		HBRUSH hPrevBrush = (HBRUSH)SelectObject(mWindowData.backBuffer, mBrushes[(UINT)eBrushColor::Gray]);
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		SelectObject(mWindowData.backBuffer, hPrevBrush);

		// 렌더링
		SceneManager::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);
		Camera::Render(mWindowData.backBuffer);

		// BitBlt 함수는 DC 간에 그림을 복사하는 함수입니다. 
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height
			, mWindowData.backBuffer, 0, 0, SRCCOPY);

		// 파괴
		SceneManager::Destroy();
	}
	void Application::createDefaultGDIObject()
	{
		// 자주 쓸 색상의 펜 생성
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		// 자주 쓸 Brush 생성
		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = (HBRUSH)GetStockObject(GRAY_BRUSH);
	}
}