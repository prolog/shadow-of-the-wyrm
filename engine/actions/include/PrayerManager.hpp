#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class PrayerManager : public IActionManager
{
  public:
    ActionCostValue pray(CreaturePtr creature);

  protected:
    friend class ActionManager;
    PrayerManager();

    ActionCostValue get_action_cost_value() const;
};
