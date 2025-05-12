#include "GroundSafetyCondition.hpp"
#include "ItemProperties.hpp"

using namespace std;

// A ground tile is safe if the creature breathes air.
bool GroundSafetyCondition::is_tile_safe(CreaturePtr creature, TilePtr tile) const
{
  bool safe = false;

  if (creature)
  {
    // Make sure the creature can breathe air.
    if (creature->can_breathe(BreatheType::BREATHE_TYPE_AIR))
    {
      safe = true;
    }
  }

  return safe;
}

#ifdef UNIT_TESTS
#include "unit_tests/GroundSafetyCondition_test.cpp"
#endif