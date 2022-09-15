#include "yaTime.h"


namespace ya
{
    Time* Time::mInstance = nullptr;

    Time::Time()
        : mCpuFrequency{}
        , mPrevFrequency{}
        , mCurFrequency{}
        , mDeltaTime(0.0f)
    {

    }

    Time::~Time()
    {

    }

    void Time::Initialize()
    {
        //CPU 의 초당 반복되는 주파수를 얻어온다.
        QueryPerformanceFrequency(&mCpuFrequency);

        //프로그램을 시작했을때의 CPU 클럭 수
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void Time::Tick()
    {
        QueryPerformanceCounter(&mCurFrequency);

        float differenceInFrequancy 
            = static_cast<float>((mCurFrequency.QuadPart - mPrevFrequency.QuadPart));

        mDeltaTime = differenceInFrequancy / static_cast<float>(mCpuFrequency.QuadPart);
        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
    }

    void Time::Render(HDC hdc)
    {
        wchar_t szFloat[50] = {};
        float fps = 1.f / mDeltaTime;

        swprintf_s(szFloat, 50, L"DeltaTime : %f", fps);
        int strLen = wcsnlen_s(szFloat, 50);

        TextOut(hdc, 10, 10, szFloat, strLen);
    }
}
