#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class SearchActionManager : public IActionManager
{
  public:
    ActionCostValue search(CreaturePtr creature);

  protected:
    friend class ActionManager;
    SearchActionManager();
    
    ActionCostValue get_action_cost_value() const;
};
