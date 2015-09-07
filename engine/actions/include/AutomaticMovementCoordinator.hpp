#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "Map.hpp"

// The automatic movement coordinator determines whether to move
// automatically, and whether to disengage automatic movement after the
// action.
class AutomaticMovementCoordinator
{
  public:
    ActionCostValue auto_move(CreaturePtr creature, MapPtr map, const Direction d);

  protected:
    // Check to see if the creature can auto-move - no unsafe statuses like
    // extreme hunger.
    //
    // Each auto-move check returns a bool (indicating whether auto-move is
    // allowed) and a string (potentially empty, which represents a string ID
    // to display if the creature is the player.
    std::pair<bool, std::vector<std::string>> creature_can_auto_move(CreaturePtr creature);
    std::pair<bool, std::vector<std::string>> creature_position_allows_auto_move(CreaturePtr creature, MapPtr map);
    std::pair<bool, std::vector<std::string>> hunger_allows_auto_move(CreaturePtr creature);

    // Check to see if the map allows auto-movement - adjacent tile must be
    // safe, non-blocking, etc.  As well, there can't be anything in the view
    // map that disallows movement (hostile creatures).
    std::pair<bool, std::vector<std::string>> fov_allows_auto_move(CreaturePtr creature, MapPtr map);
    std::pair<bool, std::vector<std::string>> tile_allows_auto_move(CreaturePtr creature, TilePtr tile);

    // Can the creature move to the current tile, based on the ones visited
    // already?  Visiting the same tile twice during auto-run is enforced
    // to ensure that there are no running loops.
    std::pair<bool, std::vector<std::string>> prev_visited_coords_allow_auto_move(CreaturePtr creature, const Coordinate& c);

    // Determine how many available moves there are from the creature's
    // current location, and set that on the creature.
    void set_available_movement_directions(CreaturePtr creature, MapPtr map);

    // Add a coordinate to the list the creature has seen during the current
    // automovement period.
    void add_coordinate_to_automove_visited(CreaturePtr creature, const Coordinate& c);
};

