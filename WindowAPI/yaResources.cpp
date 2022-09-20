#include "yaResources.h"

namespace ya
{
	Resources* Resources::mInstance = nullptr;
	Resources::Resources()
	{

	}
	
	Resources::~Resources()
	{
		std::map<std::wstring, Resource*>::iterator iter = mResources.begin();
		for (; iter != mResources.end(); ++iter)
		{
			delete(iter->second);
		}

		//for (auto iter : mResources)
		//{
		//	delete iter.second;
		//}
	}

	bool Resources::Initialize()
	{
		return false;
	}

}
