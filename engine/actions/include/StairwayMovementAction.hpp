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

    void move_to_custom_map(TilePtr current_tile, MapPtr current_map, MapExitPtr map_exit, CreaturePtr creature, MovementAction* const ma, const Direction d);
    ActionCostValue generate_or_move_to_zlevel(MovementAction* const ma, IMessageManager& manager, CreaturePtr creature, MapPtr current_map, TilePtr tile, const Coordinate& c, MapExitPtr map_exit, const ExitMovementType emt, const Direction d);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};

