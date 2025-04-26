#include "GroundSafetyCondition.hpp"
#include "ItemProperties.hpp"

using namespace std;

// A ground tile is safe if the creature breathes air.
bool GroundSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile)
{
  bool safe = false;

  if (creature)
  {
    // First, make sure the creature can breathe air.
    if (creature->can_breathe(BreatheType::BREATHE_TYPE_AIR))
    {
      safe = true;
    }

    // Next, check to see if moving there would be deathly.
    if (tile->get_unprotected_movement_is_death(creature))
    {
      safe = creature->has_item_with_property(ItemProperties::ITEM_PROPERTIES_NEXUS);
    }
  }

  return safe;
}

#ifdef UNIT_TESTS
#include "unit_tests/GroundSafetyCondition_test.cpp"
#endif