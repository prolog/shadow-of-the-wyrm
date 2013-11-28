#pragma once
#include "HungerDamageCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureHungerTimer : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    void apply_hunger_damage_if_appropriate(CreaturePtr creature, const ulonglong minutes_this_tick);

    HungerDamageCalculator hdc;
};

