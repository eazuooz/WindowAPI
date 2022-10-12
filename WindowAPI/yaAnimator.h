#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimaiton(const std::wstring& name, Image* image
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, float columnLegth, UINT spriteLength, float duration, bool bAffectedCamera = false);
		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool bLoop = false);
		//void Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offset
		//	, float step, UINT spriteLength, float duration, bool affectedCamera = false);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mPlayAnimation;
		bool mbLoop;
	};

	typedef std::map<std::wstring, Animation*>::iterator AnimationsIter;
}
