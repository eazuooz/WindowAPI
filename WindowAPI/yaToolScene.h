#pragma once

#include "yaScene.h"

namespace ya
{
	class TilePalatte;
	class ToolScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void Destroy() override;

		virtual void Enter() override;
		virtual void Exit() override;

		void CreateTile(int index, int x, int y);

		TilePalatte* GetTilePalatte() { return mTilePalette; }
		UINT GetTileIndex() { return mTileIndex; }
		void SetTileIndex(UINT index) { mTileIndex = index; }
	private:
		TilePalatte* mTilePalette;
		UINT mTileIndex;
	};
}
