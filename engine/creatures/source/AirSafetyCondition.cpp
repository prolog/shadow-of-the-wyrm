#include "AirSafetyCondition.hpp"

using namespace std;

// An air tile is safe only when a creature is flying.
//
// Otherwise, the creature plummets to its death.
bool AirSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile)
{
  bool safe = false;

  // TODO: Checks for flying and incorporeal.

  return safe;
}
