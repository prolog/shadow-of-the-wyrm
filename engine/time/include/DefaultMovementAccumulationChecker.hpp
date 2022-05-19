#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class DefaultMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;

  protected:
    void mark_skills(CreaturePtr creature, TilePtr tile);
};

