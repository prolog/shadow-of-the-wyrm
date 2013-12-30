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

    AlcoholCalculator alco_calc;
};
