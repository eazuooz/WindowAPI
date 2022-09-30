#include "yaEntity.h"

namespace ya
{
	Entity::Entity()
		: mID(reinterpret_cast<UINT64>(this))
	{
	}
	Entity::Entity(const Entity& other)
		: mID(reinterpret_cast<UINT64>(this))
		, mName(other.mName)
	{
	}
	Entity::~Entity()
	{
	}
}