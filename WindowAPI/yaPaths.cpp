#include "yaPaths.h"


namespace ya
{
	//std::filesystem::path Paths::mPath;
	wchar_t Paths::mPath[256] = {};

	Paths::Paths()
	{
		// ������ ��������
		GetCurrentDirectory(256, mPath);

		// ���������� ����
		int iLen = wcsnlen_s(mPath, 254);
		for (int i = iLen; i > 0; --i)
		{
			if ('\\' == mPath[i])
			{
				mPath[i + 1] = 0;
				break;
			}

			continue;
		}

		// + L"bin\\content"
		wcscat_s(mPath, L"bin\\Resources\\");
	}

	Paths::~Paths()
	{

	}
}
