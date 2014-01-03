#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class DeityDecisionImplications;

class PrayerAction : public IActionManager
{
  public:
    ActionCostValue pray(CreaturePtr creature);

  protected:
    friend class ActionManager;
    PrayerAction();
    
    void say_prayer(CreaturePtr creature);
    void finish_prayer(CreaturePtr creature, const DeityDecisionImplications& implications);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
