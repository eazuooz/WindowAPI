#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "Common.h"

namespace ya
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// 좌측 상단 픽셀좌표
			Vector2 size;		// 좌측 상단으로 부터 잘라낼 가로 세로 픽셀 길이
			Vector2 offset;
			float duration;			// 해당 프레임 유지시간

			Sprite()
				: leftTop(0.0f, 0.0f)
				, size(0.0f, 0.0f)
				, offset(0.0f, 0.0f)
				, duration(0.0f)
			{

			}
		};

	public:
		Animation();
		~Animation();
		
		void Tick();
		void Render(HDC hdc);
		void Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset
			, float columnLegth, UINT spriteLength, float duration, bool affectedCamera = false);

		void Reset();

		bool isComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private:
		Animator* mAnimator;
		Image* mImage;
		std::vector<Sprite> mSpriteSheet;
		int mSpriteIndex;
		float mTime;
		bool mbStart;
		bool mbComplete;
		bool mbEnd;
		bool mbAffectedCamera;




	};
}
