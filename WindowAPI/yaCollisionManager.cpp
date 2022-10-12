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
		// �� �浹ü��  ID Ȯ��
		ColliderID id;
		id.left = left->GetID();
		id.right = right->GetID();

		// ���� �浹������ �˻��Ѵ�.
		std::map<UINT64, bool>::iterator iter
			= mCollisionInfomations.find(id.ID);

		// �浹������ ���ٸ� �浹������ ������ش�.
		if (iter == mCollisionInfomations.end())
		{
			mCollisionInfomations.insert(std::make_pair(id.ID, false));
			iter = mCollisionInfomations.find(id.ID);
		}

		if (Intersect(left, right))
		{
			// �浹 ��
			if (iter->second == false)
			{
				//���� �浹������
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				//�浹 ���϶�
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// �浹 X
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


		// �� �浹ü�� �������� �Ÿ���, �� ������ ���ݳ����� ���� ���ؼ� 
		// �� ��(x, y) ���� ��ġ�� �κ��� ���ÿ� �����ϴ��� üũ�Ѵ�.
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
		// �� ���� ���ڸ� ��(�迭�� �ε���)����, �� ū ���ڸ� ��(��Ʈ ��ġ)��
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