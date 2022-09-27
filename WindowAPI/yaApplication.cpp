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


		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경 및 출력 설정
		SetWindowPos(mWindowData.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mWindowData.hWnd, true);

		// 이중 버퍼링
		// 윈도우 해상도와 동일한 크기의 비트맵을 생성
		// 새로 생성한 비트맵을 가리키는 전용 DC 생성
		// 새소 생성한 비트맵과 DC 를 서로 연결
		mWindowData.backTexture
			= CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);
		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);
		DeleteObject(defaultBitmap);

		return true;
	}

	void Application::Tick()
	{
		// 업데이트
		Time::GetInstance().Tick();
		InputManager::GetInstance().Tick();
		SceneManager::GetInstance().Tick();

		
		// Clear
		HBRUSH hPrevBrush = (HBRUSH)SelectObject(mWindowData.backBuffer, mBrushes[(UINT)eBrushColor::Gray]);
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		SelectObject(mWindowData.backBuffer, hPrevBrush);

		// 렌더링
		SceneManager::GetInstance().Render(mWindowData.backBuffer);
		Time::GetInstance().Render(mWindowData.backBuffer);

		// BitBlt 함수는 DC 간에 그림을 복사하는 함수입니다. 
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height
			, mWindowData.backBuffer, 0, 0, SRCCOPY);
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