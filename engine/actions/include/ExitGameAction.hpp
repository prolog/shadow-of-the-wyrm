#pragma once
#include "IActionManager.hpp"
#include "MessageManagerFactory.hpp"

class ExitGameAction : public IActionManager
{
  public:
    ActionCostValue save(CreaturePtr creature) const;
    ActionCostValue quit(CreaturePtr creature, const bool show_quit_actions) const;
    void create_dump_if_necessary(IMessageManager& manager, ActionManager * const am, CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class Game;

    ExitGameAction();
};
