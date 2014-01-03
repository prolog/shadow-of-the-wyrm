#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"
#include "Feature.hpp"

class KeyManager : public IActionManager
{
  public:
    bool has_key(CreaturePtr creature, LockPtr lock);

  protected:
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};

