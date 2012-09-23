#pragma once
#include <utility>
#include <boost/static_assert.hpp>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef std::pair<int, int> Coordinate;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ulonglong;
