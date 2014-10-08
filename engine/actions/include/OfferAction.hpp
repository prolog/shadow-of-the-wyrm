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
    void handle_sacrifice(CreaturePtr creature, FeaturePtr feature, ItemPtr item);
    void sacrifice_on_own_altar(CreaturePtr creature, FeaturePtr feature, ItemPtr item);
    void sacrifice_on_other_altar(CreaturePtr creature, FeaturePtr feature, ItemPtr item);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
