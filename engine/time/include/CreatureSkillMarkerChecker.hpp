#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureSkillMarkerChecker : public ICreatureRegeneration
{
  public:
    CreatureSkillMarkerChecker();
    CreatureSkillMarkerChecker(const uint new_interval);

    void tick(CreaturePtr creature, TilePtr tile, const ulonglong min_this_tick, const ulonglong total_min_elapsed) override;

  protected:
    uint minutes_interval;
};
