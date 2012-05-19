#pragma once
#include <utility>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef std::pair<int, int> Coordinate;

// The number of "ticks" an action costs.  The real minimum is 1, though certain actions (observing one's inventory,
// getting the game version, and anything else that does not affect the state of the world) will cost 0.
typedef unsigned int ActionCost;

typedef unsigned char uchar;
typedef unsigned int uint;
