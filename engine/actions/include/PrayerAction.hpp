#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class DeityDecisionImplications;

class PrayerAction : public IActionManager
{
  public:
    ActionCostValue pray(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    PrayerAction();
    
    void say_prayer(CreaturePtr creature);
    void finish_prayer(CreaturePtr creature, const DeityDecisionImplications& implications);
};
