#include "yaCollisionManager.h"

#include "yaObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaCollider.h"

namespace ya
{
	WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionInfomations;

	void CollisionManager::Tick()
	{
#ifdef _DEBUG
		std::bitset<16> bits[16];
		for (size_t i = 0; i < 16; i++)
		{
			bits[i] = mMatrix[i];
		}
#endif
		Scene* scene = SceneManager::GetPlayScene();
		for (UINT row = 0; row < _COLLIDER_LAYER; row++)
		{
			for (UINT col = row; col < _COLLIDER_LAYER; col++)
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(scene, (eColliderLayer)row, (eColliderLayer)col);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(Scene* scene, eColliderLayer leftLayer, eColliderLayer rightLayer)
	{
		const std::vector<Object*>& lefts = scene->GetObjects(leftLayer);
		const std::vector<Object*>& rights = scene->GetObjects(rightLayer);

		for (auto leftObject : lefts)
		{
			if (leftObject->GetComponent<Collider>() == nullptr)
				continue;

			for (auto rightObject : rights)
			{
				if (rightObject->GetComponent<Collider>() == nullptr)
					continue;
				if (rightObject == leftObject)
					continue;

				ColliderCollision(leftObject->GetComponent<Collider>(), rightObject->GetComponent<Collider>());
			}

			if (leftLayer == rightLayer)
				break;
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체의  ID 확인
		ColliderID id;
		id.left = left->GetID();
		id.right = right->GetID();

		// 이전 충돌정보를 검색한다.
		std::map<UINT64, bool>::iterator iter
			= mCollisionInfomations.find(id.ID);

		// 충돌정보가 없다면 충돌정보를 만들어준다.
		if (iter == mCollisionInfomations.end())
		{
			mCollisionInfomations.insert(std::make_pair(id.ID, false));
			iter = mCollisionInfomations.find(id.ID);
		}

		if (Intersect(left, right))
		{
			// 충돌 중
			if (iter->second == false)
			{
				//최초 충돌했을때
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				//충돌 중일때
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
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

#ifdef _DEBUG
		std::bitset<16> bits = mMatrix[row];
#endif
	}
}