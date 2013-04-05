#pragma once
#include "IActionManager.hpp"

// Owned/controlled by ActionManager
class CharacterDumpAction : public IActionManager
{
  public:
    ActionCostValue dump_character(CreaturePtr creature);

  protected:
    friend class ActionManager;
    CharacterDumpAction();
    
    ActionCostValue get_action_cost_value() const;
};
