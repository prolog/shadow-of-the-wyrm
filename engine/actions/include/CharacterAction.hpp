#pragma once
#include "IActionManager.hpp"

enum struct CharacterDumpType
{
  CHARACTER_DUMP_USER_INITIATED = 0,
  CHARACTER_DUMP_SYSTEM_INITIATED = 1
};

// Owned/controlled by ActionManager
class CharacterAction : public IActionManager
{
  public:
    ActionCostValue display_character(CreaturePtr creature);
    ActionCostValue dump_character(CreaturePtr creature, const CharacterDumpType cdt, const bool add_pause);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class ExitGameAction;

    CharacterAction();    
};
