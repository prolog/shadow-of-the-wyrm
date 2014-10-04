#pragma once
#include "IActionManager.hpp"
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "Feature.hpp"

class OfferAction : public IActionManager
{
  public:
    ActionCostValue offer(CreaturePtr creature, ActionManager * const am);
    
  protected:
    friend class ActionManager;
    OfferAction();
    
    void add_no_altar_message(CreaturePtr creature);
    ActionCostValue sacrifice_item(CreaturePtr creature, FeaturePtr feature, ActionManager * const am);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
