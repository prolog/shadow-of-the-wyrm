#pragma once
#include "IActionManager.hpp"
#include "Potion.hpp"

class ActionManager;

class QuaffManager : public IActionManager
{
  public:
    ActionCostValue quaff(CreaturePtr creature, ActionManager * const am);

  protected:
    void quaff_potion(CreaturePtr creature, PotionPtr potion);
    ActionCostValue get_action_cost_value() const;
};
