#pragma once
#include "IActionManager.hpp"
#include "Consumable.hpp"

// Handles details related to consuming a consumable, mostly related to
// ensuring the nutrition of the consumable is added to the creature's
// food counter.
class ConsumableAction : public IActionManager
{
  public:
    ActionCostValue consume(CreaturePtr creature, ConsumablePtr consumable, const bool process_consumable_action);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    void gain_resistances_from_consumable(CreaturePtr creature, ConsumablePtr consumable);
    bool add_consumable_message_if_necessary(CreaturePtr creature, ResistancePtr res, const double delta);
};
