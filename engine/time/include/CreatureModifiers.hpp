#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureModifiers : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;
};
