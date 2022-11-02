#include "yaTile.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	Tile::Tile(Vector2 pos)
		: Object()
		, mAtlas(nullptr)
		, x(-1)
		, y(-1)
	{
		SetPos(pos);
	}

	Tile::Tile(Image* atlas, int index)
	{
		Initialize(atlas, index);
	}

	Tile::~Tile()
	{

	}

	void Tile::Initialize(Image* atlas, int index)
	{
		mIndex = index;
		if (atlas == nullptr
			|| index < 0)
			return;
		mAtlas = atlas;

		int maxColumn = mAtlas->GetWidth() / TILE_SIZE;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE;

		y = index / maxColumn;
		x = index % maxColumn;
	}

	void Tile::SetIndex(int index)
	{
		int maxColumn = mAtlas->GetWidth() / TILE_SIZE;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE;

		y = index / maxColumn;
		x = index % maxColumn;
	}

	void Tile::Tick()
    {

    }

    void Tile::Render(HDC hdc)
    {
		if (mAtlas == nullptr)
			return;

		Vector2 renderPos = Camera::CalulatePos(GetPos());

		TransparentBlt(hdc
			, (int)renderPos.x, (int)renderPos.y
			, TILE_SIZE, TILE_SIZE
			, mAtlas->GetHdc()
			, TILE_SIZE * x, TILE_SIZE * y
			, TILE_SIZE, TILE_SIZE
			, RGB(255, 0, 255));
    }

}
