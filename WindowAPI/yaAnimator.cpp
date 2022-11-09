#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaImage.h"

namespace ya
{
	Animator::Animator(Animator& other)
		: Component(other)
		, mPlayAnimation(nullptr)
		, mbLoop(false)
	{
		//AnimationsIter iter = other.mAnimations.begin();
		for (AnimationPair animationPair : other.mAnimations)
		{
			Animation* animation = new Animation(*(animationPair.second));
			animation->SetAnimator(this);
			mAnimations.insert(std::make_pair(animationPair.first, animation));
		}
	}

	Animator::Animator()
		: Component(eComponentType::Animator)
		, mPlayAnimation(nullptr)
		, mbLoop(false)
	{
	}
	Animator::~Animator()
	{
		AnimationsIter iter = mAnimations.begin();
		for (; iter != mAnimations.end(); ++iter)
		{
			delete iter->second;
		}
	}
	void Animator::Tick()
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();
			if (mbLoop && mPlayAnimation->isComplete())
			{
				mCompleteEvent();
				mPlayAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Render(hdc);
		}
	}

	void Animator::CreateAnimaiton(const std::wstring& name, Image* image
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, float columnLegth, UINT spriteLength, float duration, bool bAffectedCamera )
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
		{
			MessageBox(nullptr, L"Animation 이름 중복", L"Animation 생성 실패", MB_OK);
			return;
		}

		animation = new Animation();
		animation->Create(image, leftTop, size, offset, columnLegth, spriteLength, duration, bAffectedCamera);
		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
	}

	void Animator::CreateAnimaitons(const std::wstring& path)
	{
		Image* spriteSheet = Image::Create(L"SPRITETEST", 100, 100);

		//BitBlt()

	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		AnimationsIter iter = mAnimations.find(name);
		if (mAnimations.end() == iter)
			return nullptr;
		
		return iter->second;
	}

	void Animator::Play(const std::wstring& name, bool bLoop)
	{
		mStartEvent();

		Animation* prevAnimation = mPlayAnimation;
		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = bLoop;

		if (prevAnimation != mPlayAnimation)
			mEndEvent();
	}
}
