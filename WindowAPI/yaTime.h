#pragma once
#include "Common.h"

namespace ya
{
	class Time
	{
	public:
		static float DeltaTime();

		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

	private:
		static LARGE_INTEGER	mCpuFrequency;
		static LARGE_INTEGER   mPrevFrequency;
		static LARGE_INTEGER	mCurFrequency;

		static float			mDeltaTime;
		static float			mOneSecond;
	};
}


