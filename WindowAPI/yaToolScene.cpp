#include "yaToolScene.h"
#include "yaApplication.h"
#include "yaTilePalette.h"
#include "yaSceneManager.h"
#include "yaImage.h"
#include "yaInputManager.h"

namespace ya
{
	void ToolScene::Initialize()
	{
		mTilePalette = new TilePalatte();
		mTileIndex = 0;
	}

	void ToolScene::Tick()
	{
		Scene::Tick();
		mTilePalette->Tick();
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);


		Pen redPen(hdc, Application::GetInstance().GetPen(ePenColor::Red));

		WindowData winData = Application::GetInstance().GetWindowData();

		int maxRow = winData.height / TILE_SIZE + 1;
		for (size_t y = 0; y < maxRow; y++)
		{
			MoveToEx(hdc, 0, TILE_SIZE * y, NULL);      //      라인(선) 시작
			LineTo(hdc, winData.width, TILE_SIZE * y);        //          라인(선) 끝
		}
		
		int maxColumn = winData.width/ TILE_SIZE + 1;
		for (size_t x = 0; x < maxColumn; x++)
		{
			MoveToEx(hdc, TILE_SIZE * x, 0, NULL);      //      라인(선) 시작
			LineTo(hdc, TILE_SIZE * x, winData.height);        //          라인(선) 끝
		}

	}

	void ToolScene::Destroy()
	{
	}

	void ToolScene::Enter()
	{
		Application::GetInstance().SetMenuBar(true);
	}

	void ToolScene::Exit()
	{
	}

	void ToolScene::CreateTile(int index, int x, int y)
	{
		mTilePalette->CreateTiles(index, x, y);
	}
}

// ======================
// Tile Count Dialog Proc
// ======================
INT_PTR CALLBACK TileCreateProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		switch (wParam)
		{
		case IDOK:
			if (LOWORD(wParam) == IDOK)
			{
				// Edit Control 에 입력한 수치를 알아낸다.
				UINT maxColumn = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
				UINT maxRow = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

				ya::Scene* pScene = ya::SceneManager::GetPlayScene();
				ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(pScene);

				if (nullptr == toolScene)
				{
					MessageBox(nullptr, L"에러", L"에러", MB_OK);
				}

				int index = toolScene->GetTileIndex();
				toolScene->CreateTile(index, maxColumn, maxRow);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;

		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}

		break;
	}
	return (INT_PTR)FALSE;
}

/// <summary>
/// TILE IMAGE Proc
/// </summary>
/// <param name="hWnd"></param>
/// <param name="message"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		DefWindowProc(hWnd, message, wParam, lParam);

		ya::WindowData atlasWindowData;
		atlasWindowData.hWnd = hWnd;
		atlasWindowData.hdc = GetDC(hWnd);
		atlasWindowData.height = 900;
		atlasWindowData.width = 800;
		ya::Application::GetInstance().SetAtlasWindow(atlasWindowData);

		ya::Scene* pScene = ya::SceneManager::GetPlayScene();
		ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(pScene);

		ya::TilePalatte* atlas = toolScene->GetTilePalatte();
		ya::Image* atlamsImg = atlas->GetImage();

		RECT rect = { 0, 0, atlamsImg->GetWidth(), atlamsImg->GetHeight()};
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(atlasWindowData.hWnd
			, nullptr, 1600, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(atlasWindowData.hWnd, true);
	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//Rectangle(GetDC(hWnd), 0, 0, 100, 100);

		ya::Scene* pScene = ya::SceneManager::GetPlayScene();
		ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(pScene);

		ya::TilePalatte* atlas = toolScene->GetTilePalatte();
		ya::Image* atlamsImg = atlas->GetImage();

		ya::Vector2 pos(ya::Vector2::Zero);

		TransparentBlt(hdc, (int)pos.x
			, (int)pos.y
			, atlamsImg->GetWidth(), atlamsImg->GetHeight()
			, atlamsImg->GetHdc(), 0, 0, atlamsImg->GetWidth(), atlamsImg->GetHeight(), RGB(255, 0, 255));

		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		if (GetFocus())
		{
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(hWnd, &mousePos);
			// 가로 8 세로 6

			int x = mousePos.x / TILE_SIZE;
			int y = mousePos.y / TILE_SIZE;

			int index = (y * 8) + (x % 8);
			ya::Scene* pScene = ya::SceneManager::GetPlayScene();
			ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(pScene);
			toolScene->SetTileIndex(index);
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}