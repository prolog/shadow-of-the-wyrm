#pragma once
#include "IActionManager.hpp"

class AutomaticMovementAction : public IActionManager
{
  public:
    ActionCostValue automatic_movement(CreaturePtr creature) const;
    ActionCostValue rest(CreaturePtr creature) const;
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

protected:
    friend class ActionManager;
    AutomaticMovementAction();    

    ActionCostValue automatic_movement_in_direction(CreaturePtr creature, MapPtr map, const Direction d) const;
};
