#pragma once
#include "yaObject.h"


namespace ya
{
	class Image;
	class Tile : public Object
	{
	public:
		Tile(Vector2 pos);
		Tile(Image* atlas, int index);
		~Tile();

		void Initialize(Image* atlas, int index);
		void SetIndex(int index);
		int GetIndex() { return mIndex; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


	private:
		Image* mAtlas;
		int mIndex;
		int x;
		int y;
	};
}
