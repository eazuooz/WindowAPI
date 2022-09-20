#pragma once
#include "Common.h"

namespace ya
{
	class Resource;
	class Resources
	{
		SINGLE(Resources)
	public:
		bool Initialize();

	private:
		std::map<std::wstring, Resource*> mResources;
	};
}
