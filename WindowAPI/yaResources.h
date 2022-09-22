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

			// �̹� ������ Ű������ �ٸ� ���ҽ��� ���� ��ϵǾ� �־���.
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			return nullptr;
		}

		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű������ Ž��
			T* resource = Find(key);
			if (nullptr != resource)
			{
				// �ش�Ű�� �̹� �ε��Ȱ� ������ �ش� ���ҽ��� ��ȯ
				return resource;
			}

			// �ش� Ű�� �ε��� ���ҽ��� ����.
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
