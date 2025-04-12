#include "GroundSafetyCondition.hpp"

using namespace std;

// A ground tile is safe if the creature breathes air.
bool GroundSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile)
{
  bool safe = false;

  if (creature)
  {
    if (creature->can_breathe(BreatheType::BREATHE_TYPE_AIR) && !tile->get_unprotected_movement_is_death(creature))
    {
      safe = true;
    }
  }

  return safe;
}

#ifdef UNIT_TESTS
#include "unit_tests/GroundSafetyCondition_test.cpp"
#endif