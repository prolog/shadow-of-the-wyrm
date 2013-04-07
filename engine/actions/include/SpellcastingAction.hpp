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

    void add_no_magical_knowledge_message() const;
    void add_invalid_spellcasting_location_message() const;
    
    ActionCostValue get_action_cost_value() const;
};
