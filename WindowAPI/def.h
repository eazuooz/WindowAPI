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

enum SCENE_TYPE
{
	LOGO,
	START,
	STAGE_01,
	END,
};