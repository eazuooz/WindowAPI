#include "yaComponent.h"



namespace ya
{
	Component::Component(Component& other)
		: mType(other.GetType())
		, mOwner(nullptr)
	{
	}
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

}
