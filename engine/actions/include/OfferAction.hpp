#pragma once
#include "IActionManager.hpp"
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "DeityDecisionImplications.hpp"
#include "Feature.hpp"

class OfferAction : public IActionManager
{
  public:
    ActionCostValue offer(CreaturePtr creature, ActionManager * const am);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    OfferAction();
    
    void add_no_altar_message(CreaturePtr creature);
    void add_piety_message_if_player(CreaturePtr creature);

    ActionCostValue sacrifice_item(CreaturePtr creature, TilePtr tile, FeaturePtr feature, ActionManager * const am);
    bool handle_sacrifice(CreaturePtr creature, TilePtr tile, FeaturePtr feature, ItemPtr item);
    bool sacrifice_on_coaligned_altar(CreaturePtr creature, FeaturePtr feature, ItemPtr item);
    bool sacrifice_on_crossaligned_altar(CreaturePtr creature, TilePtr tile, FeaturePtr feature, ItemPtr item);

    // Returns the increase in piety as the result of the sacrifice.
    int adjust_creature_piety(CreaturePtr creature, const DeityDecisionImplications& ddi);
};
