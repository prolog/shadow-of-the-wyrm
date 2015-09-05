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
};

