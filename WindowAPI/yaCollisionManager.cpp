#include "yaCollisionManager.h"

#include "yaObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaCollider.h"

namespace ya
{
	WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};
	void CollisionManager::Tick()
	{
		Scene* scene = SceneManager::GetPlayScene();

		for (UINT row = 0; row < _COLLIDER_LAYER; row++)
		{
			for (UINT col = 0; col < _COLLIDER_LAYER; col++)
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(scene, (eColliderLayer)row, (eColliderLayer)col);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
	{

		const std::vector<Object*>& lefts = scene->GetObjects(left);
		const std::vector<Object*>& rights = scene->GetObjects(right);

		for (auto leftObject : lefts)
		{
			if (leftObject->GetCollider() == nullptr)
				continue;

			for (auto rightObject : rights)
			{
				if (rightObject->GetCollider() == nullptr)
					continue;
				if (leftObject == rightObject)
					continue;

				if (Intersect(leftObject->GetCollider(), rightObject->GetCollider()))
				{
					// 충돌 중
				}
				else
				{
					// 충돌 X
				}
			}
		}
	}

	bool CollisionManager::Intersect(ya::Collider* left, ya::Collider* right)
	{
		Vector2 leftPos = left->GetPos();
		Vector2 leftScale = left->GetScale();

		Vector2 rightPos = right->GetPos();
		Vector2 rightScale = right->GetScale();


		// 두 충돌체의 중점간의 거리와, 각 면적의 절반끼리의 합을 비교해서 
		// 각 축(x, y) 별로 겹치는 부분이 동시에 존재하는지 체크한다.
		if (fabs(leftPos.x - rightPos.x) < (leftScale.x / 2.f + rightScale.x / 2.f)
			&& fabs(leftPos.y - rightPos.y) < (leftScale.y / 2.f + rightScale.y / 2.f))
		{
			return true;
		}


		return false;
	}

	void CollisionManager::clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * _COLLIDER_LAYER);
	}

	void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
	{
		// 더 작은 숫자를 행(배열의 인덱스)으로, 더 큰 숫자를 열(비트 위치)로
		UINT row = 0;
		UINT col = 0;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;
		if (iLeft <= iRight)
		{
			row = (UINT)iLeft;
			col = (UINT)iRight;
		}
		else
		{
			row = (UINT)iRight;
			col = (UINT)iLeft;
		}

		if (value == true)
			mMatrix[row] |= (1 << col);
		else
			mMatrix[row] &= ~(1 << col);
	}
}