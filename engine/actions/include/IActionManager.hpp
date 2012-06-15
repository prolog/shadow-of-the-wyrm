#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class IActionManager
{
  protected:
    // Does not take into account creature speed: this value gets added to the creature speed if the value
    // is greater than zero.
    virtual uint get_action_cost_value() const = 0;
};
