#pragma once
#include "IActionManager.hpp"

class CharacterDumpManager : public IActionManager
{
  public:
    void dump_character(CreaturePtr creature);

  protected:
    uint get_current_action_cost() const;
};
