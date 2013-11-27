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

    void explode_potion(CreaturePtr original_attacker, CreaturePtr creature_by_exploding_potion, PotionPtr potion);
    void quaff_potion(CreaturePtr creature, PotionPtr potion, CreaturePtr caster, const std::string& message);

  protected:
    Spell create_potion_spell(PotionPtr potion);
    void add_quaff_message(CreaturePtr creature, const std::string& quaff_message);
    ActionCostValue get_action_cost_value() const override;
};
