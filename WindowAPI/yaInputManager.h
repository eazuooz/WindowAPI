#pragma once
#include "Common.h"



namespace ya
{
	enum class KEY_CODE
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L, 
		Z, X, C, V, B, N, M,
		END,
	};
	enum KEY_STATE
	{
		DOWN,
		PRESSED,
		UP,
		NONE,
	};

	class InputManager
	{
		SINGLE(InputManager)

	public:
		struct Key
		{
			KEY_CODE  eType;
			KEY_STATE eState;
			bool	  bPressed;
		};

		void Initialize();
		void Tick();

		KEY_STATE GetKeyState(KEY_CODE keyCode);

	private:
		std::vector<Key> mKeys;
	};
}
