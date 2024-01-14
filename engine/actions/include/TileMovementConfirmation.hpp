#pragma once
#include <string>
#include <tuple>
#include "Creature.hpp"
#include "Map.hpp"

class TileMovementConfirmation
{
  public:
    // bool = requires confirmation
    // string = confirmation message SID
    std::tuple<bool, std::string, std::string> get_confirmation_details(CreaturePtr creature, MapPtr map, TilePtr old_tile, const Coordinate& old_tile_coords, TilePtr new_tile, const Coordinate& new_tile_coord);

  protected:
    std::tuple<bool, std::string, std::string> check_for_jumping_into_water(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile);
};
