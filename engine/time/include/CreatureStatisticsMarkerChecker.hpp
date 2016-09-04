#pragma once
#include "ICreatureRegeneration.hpp"

// This class is invoked periodically (every three hours) to see if a
// creature has any number of conditions that would potentially mark a
// statistic.  So if the creature is burdened, that will mark strength;
// if the creature is neither hungry nor full, toughness; and if the
// creature is wearing amulets and rings, charisma.
class CreatureStatisticsMarkerChecker : public ICreatureRegeneration
{
  public:
    CreatureStatisticsMarkerChecker();
    CreatureStatisticsMarkerChecker(const uint new_interval);

    void tick(CreaturePtr creature, TilePtr tile, const ulonglong min_this_tick, const ulonglong total_min_elapsed) override;

  protected:
    void check_strength_conditions(CreaturePtr creature);
    void check_health_conditions(CreaturePtr creature);
    void check_charisma_conditions(CreaturePtr creature);

    uint minutes_interval;
};
