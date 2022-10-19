#include "yaAnimation.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaCamera.h"
#include "yaImage.h"

namespace ya
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mImage(nullptr)
		, mSpriteIndex(0)
		, mTime(0.0f)
		, mbComplete(false)
		, mbAffectedCamera(false)
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::Tick()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;

			if (mSpriteSheet.size() <= mSpriteIndex + 1)
			{
				mbComplete = true;
			}
			else
			{
				mSpriteIndex += 1;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		Object* object = mAnimator->GetOwner();
		Vector2 pos = object->GetPos();
		if (mbAffectedCamera)
			pos = Camera::CalulatePos(pos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		pos += mSpriteSheet[mSpriteIndex].offset;
		AlphaBlend(hdc
			, int(pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.0f)
			, int(pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.0f)
			, int(mSpriteSheet[mSpriteIndex].size.x)
			, int(mSpriteSheet[mSpriteIndex].size.y)
			, mImage->GetHdc()
			, int(mSpriteSheet[mSpriteIndex].leftTop.x)
			, int(mSpriteSheet[mSpriteIndex].leftTop.y)
			, int(mSpriteSheet[mSpriteIndex].size.x)
			, int(mSpriteSheet[mSpriteIndex].size.y)
			, func);
	}

	void Animation::Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset
		, float columnLegth, UINT spriteLength, float duration, bool affectedCamera)
	{
		mImage = image;
		mbAffectedCamera = affectedCamera;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite;

			sprite.leftTop.x = leftTop.x + (columnLegth * float(i));
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration= duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}
}