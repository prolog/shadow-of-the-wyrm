#pragma once
#include <map>
#include "IActionManager.hpp"

class ShowResistancesAction : public IActionManager
{
  public:
    ActionCostValue show_resistances(CreaturePtr creature);

  protected:
    Colour get_resistance_text_sid(const DamageType dt);
    Colour get_resistance_text_colour(const double resist_value);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
