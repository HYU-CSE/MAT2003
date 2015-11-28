#pragma once

#ifdef WIN32
#include <Windows.h>
#pragma warning (disable : 4996)
#elif

#endif

#include <fstream>
#include <iostream>
#include <functional>
#include <cmath>
#include <string>

#include "resource.h"
#include "draw.h"

#define SIZEW 1000
#define SIZEH 500

#define SIZEWW SIZEW + 16
#define SIZEHH SIZEH + 39

extern POINT point, sPoint;
extern node* sNode, *bNode;
extern edge* sEdge;

using namespace std;