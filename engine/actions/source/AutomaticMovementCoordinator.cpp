#include "AutomaticMovementCoordinator.hpp"
#include "CoordUtils.hpp"
#include "MapUtils.hpp"
#include "MovementAction.hpp"

ActionCostValue AutomaticMovementCoordinator::auto_move(CreaturePtr creature, MapPtr map, const Direction d)
{
  AutomaticMovement& am = creature->get_automatic_movement_ref();
  ActionCostValue auto_move_cost = 0;
  bool auto_movement_engaged = false;
  TilePtr direction_tile = map->at(CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), d));

  if (creature_can_auto_move(creature) && tile_allows_auto_move(direction_tile))
  {
    MovementAction maction;
    auto_move_cost = maction.move(creature, d);

    // If the creature wasn't able to move, disengage automovement.
    if (auto_move_cost > 0)
    {
      auto_movement_engaged = true;
    }
  }

  am.set_direction(d);
  am.set_engaged(auto_movement_engaged);

  return auto_move_cost;
}

bool AutomaticMovementCoordinator::creature_can_auto_move(CreaturePtr creature)
{
  // JCD FIXME
  return true;
}

bool AutomaticMovementCoordinator::tile_allows_auto_move(TilePtr tile)
{
  // JCD FIXME
  return true;
}

