#pragma once
#include "IActionManager.hpp"

// Owned/controlled by ActionManager
class CharacterDumpManager : public IActionManager
{
  public:
    ActionCostValue dump_character(CreaturePtr creature);

  protected:
    friend class ActionManager;
    CharacterDumpManager();
    
    ActionCostValue get_action_cost_value() const;
};
