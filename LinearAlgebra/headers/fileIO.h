#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "to_string.h"

using namespace std;

#define FILE_TEST(filename, end) \
	string temp = (filename);\
	(filename) = temp + "0";\
	for(int i = 0; i < (end); (filename) = (temp) + to_string(++i))
