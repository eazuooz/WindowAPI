#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};
		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

	public:
		Animator(Animator& other);
		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimaiton(const std::wstring& name, Image* image
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, float columnLegth, UINT spriteLength, float duration, bool bAffectedCamera = false);
		void CreateAnimations(const std::wstring& path, const std::wstring& name, Vector2 offset = Vector2::Zero, float duration = 0.1f);


		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool bLoop = false);

		Events* FindEvents(const std::wstring key);
		std::function<void()>& GetStartEvent(const std::wstring key);
		std::function<void()>& GetCompleteEvent(const std::wstring key);
		std::function<void()>& GetEndEvent(const std::wstring key);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;

		Image* mSPriteSheet;
		Animation* mPlayAnimation;
		bool mbLoop;
	};

	typedef std::map<std::wstring, Animation*>::iterator AnimationsIter;
	typedef std::pair<std::wstring, Animation*> AnimationPair;
}
