#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class OfferAction : public IActionManager
{
  public:
    ActionCostValue offer(CreaturePtr creature);
    
  protected:
    friend class ActionManager;
    OfferAction();
    
    void add_no_altar_message(CreaturePtr creature);
    ActionCostValue sacrifice_item(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
