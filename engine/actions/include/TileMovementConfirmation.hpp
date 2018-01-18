#pragma once
#include <string>
#include <utility>
#include "Creature.hpp"
#include "Map.hpp"

class TileMovementConfirmation
{
  public:
    // bool = requires confirmation
    // string = confirmation message SID
    std::pair<bool, std::string> get_confirmation_details(CreaturePtr creature, MapPtr map, TilePtr old_tile, const Coordinate& old_tile_coords, TilePtr new_tile, const Coordinate& new_tile_coord);

  protected:
    std::pair<bool, std::string> check_for_jumping_into_water(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile);
};
