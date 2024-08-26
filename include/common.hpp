#pragma once
#include <map>
#include <utility>
#include <vector>

// Only supports Win/*nix/OS X for now
const char FS_PATH_SEPARATOR =
#ifdef _WIN32
'\\';
#else
'/';
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

using Coordinate = std::pair<int, int>;
using uchar = unsigned char;
using uint = unsigned int;
using ulonglong = unsigned long long;

enum struct ternary
{
	TERNARY_UNDEFINED = -1,
	TERNARY_FALSE = 0,
	TERNARY_TRUE = 1
};
