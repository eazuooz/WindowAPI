#pragma once
#include "Common.h"

namespace ya
{
	class Resource;
	class Image;

	template <typename T>
	class Resources
	{
	public:
		static T* Find(const std::wstring& key)
		{
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			return nullptr;
		}

		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			T* resource = Find(key);
			if (nullptr != resource)
			{
				// 해당키로 이미 로딩된게 있으면 해당 리소스를 반환
				return resource;
			}

			// 해당 키로 로딩된 리소스가 없다.
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Image Load Failed!", L"Error", MB_OK);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

	private:
		Resources() 
		{
		
		}
		~Resources()
		{
			Release();
		}

		void Release()
		{
			std::map<std::wstring, Resource*>::iterator iter = mResources.begin();
			for (; iter != mResources.end(); ++iter)
			{
				delete(iter->second);
			}
		}
		
	private:
		static std::map<std::wstring, Resource*> mResources;
	};

	template <typename T> 
	std::map<std::wstring, Resource*> Resources<T>::mResources;
}
