#pragma once
#define SINGLE(type)\
public:\
	static type& GetInstance()\
	{\
		static type mInstance;\
		return mInstance;\
	}\
private:\
	type();\
	~type();

#define KEY_PREESED(KEY) ya::KEY_STATE::PRESSED == ya::InputManager::GetInstance().GetKeyState(KEY)
#define KEY_DOWN(KEY) ya::KEY_STATE::DOWN == ya::InputManager::GetInstance().GetKeyState(KEY)
#define KEY_UP(KEY) ya::KEY_STATE::UP == ya::InputManager::GetInstance().GetKeyState(KEY)

#define _COLLIDER_LAYER 16

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
	Transparent, // 투명 브러쉬
	Black,  // 검은 브러쉬
	Gray,	// 회색 브러쉬
	End,
};

enum class eComponentType
{
	Collider,
	Animator,
	Gravity,
	End,
};

enum class eColliderLayer
{
	DEFAULT,
	BACKGROUND,
	TILE,
	PLAYER,
	PLAYER_PROJECTILE,
	MONSTER,
	MONSTER_PROJECTILE,


	UI = _COLLIDER_LAYER - 1,
	END = _COLLIDER_LAYER,
};

