#pragma once
#include "AlcoholCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureAlcoholTimer : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    void absorb_alcohol(CreaturePtr creature);
    void metabolize_alcohol(CreaturePtr creature);

    // Add a message if the creature has become drunk or sober.
    void add_inebriation_message_if_necessary(CreaturePtr creature, bool drunk_before, bool drunk_after);

    // Check to see if the creature has died through alcohol poisoning.
    void check_for_alcohol_poisoning_death(CreaturePtr creature);

    AlcoholCalculator alco_calc;
};
