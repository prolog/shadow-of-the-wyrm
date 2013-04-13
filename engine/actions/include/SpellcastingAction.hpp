#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class SpellcastingAction : public IActionManager
{
  public:
    ActionCostValue cast_spell(CreaturePtr creature) const;
    
  protected:
    friend class ActionManager;
    SpellcastingAction();

    // Internal spellcasting function that is called by the basic cast_spell(creature)
    // function.
    ActionCostValue cast_spell(CreaturePtr creature, const std::string& spell_id) const;

    void add_no_magical_knowledge_message() const;
    void add_invalid_spellcasting_location_message() const;
    void add_insufficient_power_message() const;
    
    ActionCostValue get_action_cost_value() const;
};
