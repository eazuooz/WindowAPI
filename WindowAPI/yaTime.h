#pragma once
#include "Common.h"

namespace ya
{
	class Time
	{
		SINGLE(Time)

	public:
		static float DeltaTime();

		void Initialize();
		void Tick();
		void Render(HDC hdc);

	private:
		LARGE_INTEGER	mCpuFrequency;
		LARGE_INTEGER   mPrevFrequency;
		LARGE_INTEGER	mCurFrequency;

		float			mDeltaTime;
		float			mOneSecond;
	};
}


