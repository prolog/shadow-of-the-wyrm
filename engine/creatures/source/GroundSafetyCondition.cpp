#include "GroundSafetyCondition.hpp"

using namespace std;

// A ground tile is safe if the creature breathes air.
bool GroundSafetyCondition::is_safe(CreaturePtr creature, TilePtr /*tile*/)
{
  bool safe = false;

  if (creature)
  {
    if (creature->can_breathe(BreatheType::BREATHE_TYPE_AIR))
    {
      safe = true;
    }
  }

  return safe;
}

