#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class ChatManager : public IActionManager
{
  public:
    ActionCostValue chat(CreaturePtr creature) const;

  protected:
    friend class ActionManager;
    ChatManager();

    ActionCostValue get_action_cost_value() const;
    ActionCostValue get_nochat_action_cost_value() const;
};

