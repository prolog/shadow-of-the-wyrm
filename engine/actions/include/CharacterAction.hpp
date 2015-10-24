#pragma once
#include "IActionManager.hpp"

// Owned/controlled by ActionManager
class CharacterAction : public IActionManager
{
  public:
    ActionCostValue display_character(CreaturePtr creature);
    ActionCostValue dump_character(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    CharacterAction();    
};
