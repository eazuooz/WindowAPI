#pragma once
#include "framework.h"
#include "Client.h"
#include "Common.h"

// 우리의 메인 프로그램
// Singleton patten

namespace ya
{
	class Application
	{
		SINGLE(Application)
	public:
		bool Initialize(WindowData& data);
		bool InitializeWindow(WindowData& data);
		void Tick();

		void SetMenuBar(bool power);
		void SetAtlasWindow(WindowData data) { mAtlasWindow = data; }

		WindowData& GetWindowData() { return mWindow; }
		WindowData& GetAtlasWindowData() { return mAtlasWindow; }
		HDC GetHdc() { return mWindow.hdc; }
		HPEN GetPen(ePenColor color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(eBrushColor brush) { return mBrushes[(UINT)brush]; }
		
	private:
		void createDefaultGDIObject();

	private:
		static int mIsStatic;
		
		WindowData mWindow;
		WindowData mAtlasWindow;

		HPEN mPens[(UINT)ePenColor::End];
		HBRUSH mBrushes[(UINT)eBrushColor::End];
		HMENU mMenuBar;
	};
}
