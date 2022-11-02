#include "yaTilePalette.h"
#include "yaInputManager.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaToolScene.h"
#include "yaGameObject.h"



namespace ya
{

	TilePalatte::TilePalatte()
		: mImage(nullptr)
	{
		mImage
			= Resources::Load<Image>(L"TileAtlas", L"..\\Resources\\Images\\Tile.bmp");
	}

	TilePalatte::~TilePalatte()
	{
	}

	void TilePalatte::Tick()
	{
		if (KEY_PREESED(KEY_CODE::LBTN))
		{
			if (GetFocus())
			{
				POINT pos = GetTilePos();
				Scene* pScene = SceneManager::GetPlayScene();
				ToolScene* toolScene = dynamic_cast<ToolScene*>(pScene);
				CreateTile(toolScene->GetTileIndex(), Vector2(pos.x, pos.y));
			}
		}
	}

	void TilePalatte::Render(HDC hdc)
	{

	}

	void TilePalatte::CreateTiles(int index, int width, int height)
	{
		for (UINT column = 0; column < height; ++column)
		{
			for (UINT row = 0; row < width; ++row)
			{
				Vector2 pos = Vector2((float)(column * TILE_SIZE), (float)(row * TILE_SIZE));
				Tile* tile = 
					gameObject::Instantiate<Tile>(pos, eColliderLayer::Tile);
				//mTiles.insert(pos);
			}
		}
	}
	void TilePalatte::CreateTile(int index, Vector2 pos)
	{
		//Vector2 key = pos;
		TileID key(pos.x, pos.y);
		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.find(key.ID);
		if (iter != mTiles.end())
		{
			iter->second->SetIndex(index);
			return;
		}

		pos *= TILE_SIZE;
		Tile* tile = gameObject::Instantiate<Tile>(pos, eColliderLayer::Tile);
		Scene* pScene = SceneManager::GetPlayScene();
		ToolScene* toolScene = dynamic_cast<ToolScene*>(pScene);

		tile->Initialize(mImage, toolScene->GetTileIndex());
		mTiles.insert(std::make_pair(key.ID, tile));

		return;
	}
	void TilePalatte::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		// 파일 입출력
		FILE* pFile = nullptr;

		// 쓰기 모드로 열기
		_wfopen_s(&pFile, szFilePath, L"wb");

		if (nullptr == pFile)
			return;

		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.begin();
		for (; iter != mTiles.end(); ++iter)
		{
			int index = (*iter).second->GetIndex();
			fwrite(&index, sizeof(int), 1, pFile);
			TileID id;
			id.ID = (*iter).first;
			fwrite(&id.ID, sizeof(UINT64), 1, pFile);
		}

		fclose(pFile);
	}

	void TilePalatte::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");
		
		if (pFile == nullptr)
			return;

		while (true)
		{
			int index = 0;
			TileID id;

			if (fread(&index, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&id, sizeof(UINT64), 1, pFile) == NULL)
				break;

			CreateTile(index, Vector2(id.left, id.right));
		}

		fclose(pFile);
	}

	POINT TilePalatte::GetTilePos()
	{
		WindowData winData 
			= Application::GetInstance().GetWindowData();

		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(winData.hWnd, &mousePos);

		int y = mousePos.y / TILE_SIZE;
		int x = mousePos.x / TILE_SIZE;
		
		POINT tilePos(x, y);
		return tilePos;
	}
}