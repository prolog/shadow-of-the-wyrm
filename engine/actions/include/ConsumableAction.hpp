#pragma once
#include "IActionManager.hpp"
#include "Consumable.hpp"

// Handles details related to consuming a consumable, mostly related to
// ensuring the nutrition of the consumable is added to the creature's
// food counter.
class ConsumableAction : public IActionManager
{
  public:
    ActionCostValue consume(CreaturePtr creature, ConsumablePtr consumable);

  protected:
    ActionCostValue get_action_cost_value() const override;
};
