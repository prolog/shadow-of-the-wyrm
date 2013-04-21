#pragma once
#include "APRegenerationCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureAPRegeneration : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed);

  protected:
    APRegenerationCalculator ap_regen_calc;
};
