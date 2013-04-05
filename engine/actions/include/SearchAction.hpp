#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class SearchAction : public IActionManager
{
  public:
    ActionCostValue search(CreaturePtr creature);

  protected:
    friend class ActionManager;
    SearchAction();
    
    ActionCostValue get_action_cost_value() const;
};
