#pragma once
#include "Common.h"


namespace ya
{
	enum class eCameraEffect
	{
		Fade_In,
		Fade_Out,
		None,
	};

	class Object;
	class Image;
	class Camera
	{
	public:
		struct EffectInfo
		{
			eCameraEffect effect;
			float duration;
			float time;
		};

	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static void PushEffect(eCameraEffect effect, float duration);
		static Vector2 CalulatePos(Vector2 pos) { return pos - mDistance; }
		static void SetTarget(Object* object) { mTarget = object; }

	private:
		Camera() = delete;
		~Camera() = delete;

	private:
		static Size mResolution;		// 화면 해상도
		static Vector2 mLookPosition;  // 카메라가 보고있는 좌표
		static Vector2 mDistance;		// 화면 해상도 중심 좌표와 현재 카메라 Look 간의 차이
		static Object* mTarget;
		
		static std::queue<EffectInfo> mEffectQueue;
		static Image* mCutton;
		static float mCuttonAlpha;
	};
}
