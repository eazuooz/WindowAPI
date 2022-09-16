#pragma once
#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>

#include "yaMath.h"
#include "def.h"




//using std::vector;
//using std::list;
//using std::map;
//using std::make_pair;
//using std::string;
//using std::wstring;
using Pos = POINT;

struct WindowData
{
    HWND hWnd;
    HDC  hdc;
    UINT height;
    UINT width;

    void Clear()
    {
        hWnd = NULL;
        hdc = NULL;
        height = 0;
        width = 0;
    }
};




