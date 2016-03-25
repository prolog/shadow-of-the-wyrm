#pragma once
#include "IActionManager.hpp"

class HelpAction : public IActionManager
{
  public:
    ActionCostValue help(CreaturePtr creature) const;
    ActionCostValue keybindings() const;
    ActionCostValue introduction_roguelikes() const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class HelpCommandProcessor;
    HelpAction();
};
