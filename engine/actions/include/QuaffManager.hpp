#pragma once
#include "IActionManager.hpp"
#include "Potion.hpp"

class ItemIdentifier;
class ActionManager;

class QuaffManager : public IActionManager
{
  public:
    bool operator==(const QuaffManager& qm);
    ActionCostValue quaff(CreaturePtr creature, ActionManager * const am);

  protected:
    void quaff_potion(CreaturePtr creature, ActionManager * const am, PotionPtr potion);
    void add_quaff_message(CreaturePtr creature, PotionPtr potion, const ItemIdentifier& item_id);
    ActionCostValue get_action_cost_value() const;
};
