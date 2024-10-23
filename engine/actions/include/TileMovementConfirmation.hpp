#pragma once
#include <string>
#include <tuple>
#include "Creature.hpp"
#include "Map.hpp"
#include "TileMovementConfirmationDetails.hpp"

class TileMovementConfirmation
{
  public:
    TileMovementConfirmationDetails get_confirmation_details(CreaturePtr creature, MapPtr map, TilePtr old_tile, const Coordinate& old_tile_coords, TilePtr new_tile, const Coordinate& new_tile_coord);

  protected:
    TileMovementConfirmationDetails check_for_jumping_into_water(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile);
};
