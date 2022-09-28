#pragma once
#include "Common.h"


namespace ya
{
	class Scene;
	class Collider;
	class CollisionManager
	{
	public:
		static void Tick();
		static void LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right);
		static bool Intersect(Collider* left, Collider* right);

		static void clear();
		static void SetLayer(eColliderLayer left, eColliderLayer right, bool value);
		
	private:
		static WORD mMatrix[_COLLIDER_LAYER];
	};
}


