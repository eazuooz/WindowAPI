#pragma once
#include "Common.h"

namespace ya
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() { return mName; }
		UINT64 GetID() { return mID; }

	private:
		std::wstring mName;
		const UINT64 mID;
		
	};
}


