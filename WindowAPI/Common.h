#pragma once

#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;

struct WindowImplData
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

struct Vector2
{
    float y;
    float x;
};

using Pos = POINT;
