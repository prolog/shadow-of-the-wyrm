#include "CreationUtils.hpp"

// The maximum number of times the creature generation algorithm can fail to place creatures before the
// algorithm is terminated.
const uint CreationUtils::MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS = 100;

CreationUtils::CreationUtils()
{
}

CreationUtils::~CreationUtils()
{
}

// The maximum number of creatures that can be on a map via random placement.
uint CreationUtils::random_maximum_creatures(const int map_height, const int map_width)
{
  return (map_height / 4) + (map_width / 4);
}

Rarity CreationUtils::generate_rarity()
{
  // JCD FIXME
  return RARITY_COMMON;
}
