#pragma once
#include "IActionManager.hpp"

// Owned/controlled by ActionManager
class CharacterDumpManager : public IActionManager
{
  public:
    void dump_character(CreaturePtr creature);

  protected:
    friend class ActionManager;
    CharacterDumpManager();
    
    uint get_action_cost_value() const;
};
