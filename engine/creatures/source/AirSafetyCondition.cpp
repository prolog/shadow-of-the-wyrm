#include "AirSafetyCondition.hpp"
#include "ItemProperties.hpp"

using namespace std;

// An air tile is safe only when a creature is flying or incorporeal.
//
// Otherwise, the creature plummets to its death.
bool AirSafetyCondition::is_tile_safe(CreaturePtr creature, TilePtr /*tile*/) const
{
  bool safe = false;

  if (creature)
  {
    safe = creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL) || 
           creature->has_status(StatusIdentifiers::STATUS_ID_FLYING);
  }

  return safe;
}

#ifdef UNIT_TESTS
#include "unit_tests/AirSafetyCondition_test.cpp"
#endif