#pragma once

#ifdef WIN32
#include <Windows.h>
#pragma warning (disable : 4996)
#elif

#endif

#include <fstream>
#include <iostream>

#include "resource.h"
#include "table.h"

#define SIZEW 800
#define SIZEH 400

#define SIZEWW SIZEW + 16
#define SIZEHH SIZEH + 39

static POINT point;

using namespace std;