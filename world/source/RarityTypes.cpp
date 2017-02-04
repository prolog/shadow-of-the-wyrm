#include "RarityTypes.hpp"

using namespace std;

Rarity& operator--(Rarity &r)
{
  if (r != Rarity::RARITY_COMMON)
  {
    r = static_cast<Rarity>(static_cast<int>(r) - 1);
  }

  return r;
}

Rarity operator--(Rarity& r, int)
{
  Rarity tmp(r);
  --r;
  return tmp;
}

#ifdef UNIT_TESTS
#include "unit_tests/RarityTypes_test.cpp"
#endif