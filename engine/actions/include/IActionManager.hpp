#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class IActionManager
{
  public:
    ActionCost get_total_action_cost(CreaturePtr creature);
  
  private:
    ActionCost create_action_cost(CreaturePtr creature);
    
  protected:
    virtual uint get_current_action_cost() const = 0;
};
