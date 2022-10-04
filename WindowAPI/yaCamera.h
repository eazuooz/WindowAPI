#pragma once
#include "Common.h"


namespace ya
{
	class Object;
	class Camera
	{
	public:
		static void Initialize();
		static void Tick();

		static Vector2 CalulatePos(Vector2 pos) { return pos - mDistance; }
		static void SetTarget(Object* object) { mTarget = object; }

	private:
		Camera() = delete;
		~Camera() = delete;

	private:
		static Size mResolution;		// ȭ�� �ػ�
		static Vector2 mLookPosition;  // ī�޶� �����ִ� ��ǥ
		static Vector2 mDistance;		// ȭ�� �ػ� �߽� ��ǥ�� ���� ī�޶� Look ���� ����

		static Object* mTarget;
	};
}
