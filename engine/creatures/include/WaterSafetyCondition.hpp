#include "ITileSafetyCondition.hpp"

// A class used to determine if a tile is safe, given that it has a super
// type of water.
class WaterSafetyCondition : public ITileSafetyCondition
{
  public:
    bool is_safe(CreaturePtr creature, TilePtr tile);
};

