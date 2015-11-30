#pragma once

#include <sstream>
#include <string>

//with MinGW(gcc for windows) can't find to_string function(standard in C++11)
//so override to_string() function,
template<typename T>
std::string to_string(const T& v)
{
	std::ostringstream oss;
	oss << v;
	return oss.str();
}