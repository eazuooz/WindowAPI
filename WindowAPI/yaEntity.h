#pragma once
#include "Common.h"

namespace ya
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const wstring& name) { mName = name; }
		const wstring& GetName() { return mName; }

	private:
		wstring mName;
	};
}


