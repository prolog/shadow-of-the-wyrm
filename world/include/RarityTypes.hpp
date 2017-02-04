#pragma once
// General rarity enumeration
enum struct Rarity
{
  RARITY_COMMON = 0,
  RARITY_UNCOMMON = 1,
  RARITY_RARE = 2,
  RARITY_VERY_RARE = 3
};

// Decrement rarity - no wrapping.
Rarity& operator--(Rarity &r);
Rarity operator--(Rarity& r, int);
