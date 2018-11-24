#include "CreationUtils.hpp"
#include "RNG.hpp"

// The maximum number of times the creature generation algorithm can fail to place creatures before the
// algorithm is terminated.
const uint CreationUtils::MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS = 180;
const uint CreationUtils::MAX_UNSUCCESSFUL_ITEM_ATTEMPTS = 120;

CreationUtils::CreationUtils()
{
}

CreationUtils::~CreationUtils()
{
}

// The maximum number of creatures that can be on a map via random placement.
uint CreationUtils::random_maximum_creatures(const int map_height, const int map_width)
{
  return (map_height / 4) + (map_width / 4)  + 1;
}

// The max number of items that can be created via random placement.
uint CreationUtils::random_maximum_items(const int map_height, const int map_width)
{
  return (map_height / 4) + (map_width / 4) + 1;
}

Rarity CreationUtils::generate_rarity()
{
  int rand = RNG::range(1, 100);

  if (rand < 75)
  {
    return Rarity::RARITY_COMMON;
  }
  else if (rand < 91)
  {
    return Rarity::RARITY_UNCOMMON;
  }
  else 
  {
    return Rarity::RARITY_RARE;
  }
}
