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



#define KEY_PREESED(KEY) ya::KEY_STATE::PRESSED == ya::InputManager::GetKeyState(KEY)
#define KEY_DOWN(KEY) ya::KEY_STATE::DOWN == ya::InputManager::GetKeyState(KEY)
#define KEY_UP(KEY) ya::KEY_STATE::UP == ya::InputManager::GetKeyState(KEY)

#define _COLLIDER_LAYER 16
#define TILE_SIZE 64
#define TILE_LINE_Y 6
#define TILE_LINE_X 8

enum eSceneType
{
	Logo,
	Start,
	Stage_01,
	Tool,
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
	Rigidbody,
	End,
};

enum class eColliderLayer
{
	Default,
	BackGround,
	Tile,
	Player,
	PlayerProjecttile,
	Monster,
	MosterProjectile,
	Ground,

	Ui = _COLLIDER_LAYER - 1,
	End = _COLLIDER_LAYER,
};

enum class eUIType
{
	HP,
	MP,
	SHOP,
	INVENTORY,
	OPTION,


	End,
};

union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};
	UINT64 ID;

	ColliderID()
	{

	}

	ColliderID(int x, int y)
	{
		left = x;
		right = y;
	}
};
typedef ColliderID TileID;

