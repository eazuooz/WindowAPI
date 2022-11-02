#pragma once
#include "yaObject.h"
#include "yaTile.h"
#include "yaImage.h"

namespace ya
{
	class TilePalatte 
	{
	public:
		TilePalatte();
		~TilePalatte();

		void Tick() ;
		void Render(HDC hdc) ;

		void CreateTiles(int index, int width, int height);
		void CreateTile(int index, Vector2 pos);
		void Save();
		void Load();

		POINT GetTilePos();

		Image* GetImage() { return mImage; }

	private:
		Image* mImage;

		std::unordered_map<UINT64, Tile*> mTiles;
	};
}