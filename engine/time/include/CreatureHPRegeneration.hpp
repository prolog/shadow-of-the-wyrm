#pragma once
#include "HPRegenerationCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureHPRegeneration : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    HPRegenerationCalculator hp_regen_calc;

    static const int PCT_CHANCE_MARK_STATISTIC;
};
