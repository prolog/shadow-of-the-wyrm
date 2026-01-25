#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureVigilanceTimer : public ICreatureRegeneration
{
  public:
    CreatureVigilanceTimer();
    CreatureVigilanceTimer(const uint new_interval);

    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    uint interval;
};
