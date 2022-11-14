#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaImage.h"
#include "yaResources.h"

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
		//std::map<std::wstring, Animation*> mAnimations;
		for (auto iter : mAnimations)
		{
			delete iter.second;
		}

		//std::map<std::wstring, Events*> mEvents;
		for (auto iter : mEvents)
		{
			delete iter.second;
		}
	}
	void Animator::Tick()
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();

			if (mbLoop && mPlayAnimation->isComplete())
			{
				Animator::Events* events
					= FindEvents(mPlayAnimation->GetName());
				if (events != nullptr)
					events->mCompleteEvent();

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

	void Animator::CreateAnimations(const std::wstring& path, const std::wstring& name, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images;
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();;
			std::wstring fullName = path + L"\\" + fileName;
			Image* image = Resources::Load<Image>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		mSPriteSheet = Image::Create(name, width * fileCount, height);
		int index = 0;
		for (Image* image : images)
		{
			BitBlt(mSPriteSheet->GetHdc(), width * index, 0, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);
			index++;
		}

		CreateAnimaiton(name, mSPriteSheet
			, Vector2(0.0f, 0.0f), Vector2(width, height)
			, offset, fileCount, fileCount, duration);
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
		Animator::Events* events = FindEvents(name);
		if (events != nullptr)
			events->mStartEvent();

		Animation* prevAnimation = mPlayAnimation;
		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = bLoop;

		if (prevAnimation != mPlayAnimation)
		{
			if (events != nullptr)
				events->mEndEvent();
		}
	}

	Animator::Events* Animator::FindEvents(const std::wstring key)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(key);
		if (iter == mEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->mStartEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->mCompleteEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->mEndEvent.mEvent;
	}
}
