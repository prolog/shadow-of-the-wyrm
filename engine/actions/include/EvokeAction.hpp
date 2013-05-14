#pragma once
#include "IActionManager.hpp"
#include "Wand.hpp"

class ItemIdentifier;
class ActionManager;

class EvokeAction : public IActionManager
{
  public:
    ActionCostValue evoke(CreaturePtr creature, ActionManager * const am);

  protected:
    ActionCostValue evoke_wand(CreaturePtr creature, ActionManager * const am, WandPtr wand);
    void add_evocation_message(CreaturePtr creature, WandPtr wand, const ItemIdentifier& item_id);

    std::pair<bool, Direction> get_evocation_direction(CreaturePtr creature);

    ActionCostValue get_action_cost_value() const;
};
