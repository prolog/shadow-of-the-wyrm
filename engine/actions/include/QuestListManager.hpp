#pragma once
#include "IActionManager.hpp"

// Creates the screens to display the in-progress and completed quests.
class QuestListManager : public IActionManager
{
  public:
    ActionCostValue quest_list() const;
    
  protected:
    friend class ActionManager;
    QuestListManager();
    
    ActionCostValue get_action_cost_value() const;
};
