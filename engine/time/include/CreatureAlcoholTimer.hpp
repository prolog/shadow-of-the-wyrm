#pragma once
#include "AlcoholCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureAlcoholTimer : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    void absorb_alcohol(CreaturePtr creature);
    void metabolize_alcohol(CreaturePtr creature);

    // Add a message if the creature has become drunk or sober.
    void add_inebriation_message_if_necessary(CreaturePtr creature, bool drunk_before, bool drunk_after);

    AlcoholCalculator alco_calc;
};
