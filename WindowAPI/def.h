#pragma once
#define SINGLE(type)\
public:\
	static type& GetInstance()\
	{\
		if (mInstance == nullptr)\
		{\
			mInstance = new type();\
		}\
		return *mInstance;\
	}\
private:\
	static type* mInstance;\
	type();\
	~type();

#define KEY_PREESED(KEY) ya::KEY_STATE::PRESSED == ya::InputManager::GetInstance().GetKeyState(KEY)
#define KEY_DOWN(KEY) ya::KEY_STATE::DOWN == ya::InputManager::GetInstance().GetKeyState(KEY)
#define KEY_UP(KEY) ya::KEY_STATE::UP == ya::InputManager::GetInstance().GetKeyState(KEY)

enum eSceneType
{
	Logo,
	Start,
	Stage_01,
	End,
};

enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent, // ���� �귯��
	Black,  // ���� �귯��
	Gray,	// ȸ�� �귯��
	End,
};

enum class eComponentType
{
	Collider,
	Animator,
	Gravity,
	End,
};

