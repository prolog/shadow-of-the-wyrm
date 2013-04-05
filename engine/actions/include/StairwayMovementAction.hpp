#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Map.hpp"

class MovementManager;

// Encapsulates the logic specific to moving via staircases and the
// associated ascend/descend logic.  More general movement (within maps,
// etc) is handled by the MovementManager.
class StairwayMovementAction : public IActionManager
{
  public:
    ActionCostValue ascend(CreaturePtr creature, MovementAction * const ma);
    ActionCostValue descend(CreaturePtr creature, MovementAction * const ma);

  protected:
    friend class MovementAction;
    StairwayMovementAction();
    ~StairwayMovementAction();

    ActionCostValue get_action_cost_value() const;
};

