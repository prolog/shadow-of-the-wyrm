#pragma once
#include "IActionManager.hpp"
#include "Potion.hpp"
#include "Spell.hpp"

class ItemIdentifier;
class ActionManager;

class QuaffAction : public IActionManager
{
  public:
    bool operator==(const QuaffAction& qa) const;
    ActionCostValue quaff(CreaturePtr creature, ActionManager * const am);

  protected:
    Spell create_potion_spell(PotionPtr potion);
    void quaff_potion(CreaturePtr creature, ActionManager * const am, PotionPtr potion);
    void add_quaff_message(CreaturePtr creature, PotionPtr potion, const ItemIdentifier& item_id);
    ActionCostValue get_action_cost_value() const;
};
