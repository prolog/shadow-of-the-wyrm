#include "ITileSafetyCondition.hpp"

// A class used to determine if a tile is safe, given that it has a super
// type of ground.  Basically, the creature just has to be an air-breather.
class GroundSafetyCondition : public ITileSafetyCondition
{
  public:
    bool is_safe(CreaturePtr creature, TilePtr tile) override;
};

