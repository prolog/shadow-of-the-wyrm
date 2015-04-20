#pragma once
#include "IActionManager.hpp"

// Creates the screens to display the in-progress and completed quests.
class QuestListAction : public IActionManager
{
  public:
    ActionCostValue quest_list() const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    QuestListAction();    
};
