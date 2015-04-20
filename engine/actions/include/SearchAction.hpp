#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class SearchAction : public IActionManager
{
  public:
    ActionCostValue search(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    SearchAction();
};
