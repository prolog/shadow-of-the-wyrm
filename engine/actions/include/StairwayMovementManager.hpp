#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Map.hpp"

class MovementManager;

// Encapsulates the logic specific to moving via staircases and the
// associated ascend/descend logic.  More general movement (within maps,
// etc) is handled by the MovementManager.
class StairwayMovementManager : public IActionManager
{
  public:
    ActionCostValue ascend(CreaturePtr creature, MovementManager * const mm);
    ActionCostValue descend(CreaturePtr creature, MovementManager * const mm);

  protected:
    friend class MovementManager;
    StairwayMovementManager();
    ~StairwayMovementManager();

    ActionCostValue get_action_cost_value() const;
};

