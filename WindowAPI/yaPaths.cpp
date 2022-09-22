#include "yaPaths.h"


namespace ya
{
	//std::filesystem::path Paths::mPath;
	wchar_t Paths::mPath[256] = {};

	Paths::Paths()
	{
		// 실행경로 가져오기
		GetCurrentDirectory(256, mPath);

		// 상위폴더로 변경
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
