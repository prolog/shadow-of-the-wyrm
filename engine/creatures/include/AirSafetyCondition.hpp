#include "ITileSafetyCondition.hpp"

// A class used to determine if an Air tile is safe.
class AirSafetyCondition : public ITileSafetyCondition
{
  public:
    bool is_safe(CreaturePtr creature, TilePtr tile) override;
};

