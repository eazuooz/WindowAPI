#pragma once
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

		WindowData& GetWindowData() { return mWindowData; }
		HPEN GetPen(PEN_COLOR color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(BRUSH_COLOR brush) { return mBrushes[(UINT)brush]; }
		
	private:
		void createDefaultGDIObject();

	private:
		static int mIsStatic;
		
		WindowData mWindowData;
		HPEN mPens[(UINT)PEN_COLOR::END];
		HBRUSH mBrushes[(UINT)BRUSH_COLOR::END];
	};
}
