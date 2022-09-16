#include "yaInputManager.h"


namespace ya
{
	int ASCII[(UINT)KEY_CODE::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};
	
	InputManager* InputManager::mInstance = nullptr;

	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::Initialize()
	{
		for (UINT i = 0; i < (UINT)KEY_CODE::END; i++)
		{
			Key key;
			key.eType = (KEY_CODE)i;
			key.eState = KEY_STATE::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void InputManager::Tick()
	{
		for (UINT i = 0; i < (UINT)KEY_CODE::END; ++i)
		{
			// 해당키가 현재 눌려있다.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// 이전 프레임에도 눌려 있었다.
				if (mKeys[i].bPressed)
					mKeys[i].eState = KEY_STATE::PRESSED;
				else
					mKeys[i].eState = KEY_STATE::DOWN;
				
				mKeys[i].bPressed = true;
			}
			else // 해당키가 현재 안눌려있다.
			{
				// 이전 프레임에는 눌려 있었다.
				if (mKeys[i].bPressed)
					mKeys[i].eState = KEY_STATE::UP;
				else // 이전 프레임에도 안눌려 있었다.
					mKeys[i].eState = KEY_STATE::NONE;

				mKeys[i].bPressed = false;
			}
		}
	}

	KEY_STATE InputManager::GetKeyState(KEY_CODE keyCode)
	{
		return mKeys[static_cast<UINT>(keyCode)].eState;
	}
}