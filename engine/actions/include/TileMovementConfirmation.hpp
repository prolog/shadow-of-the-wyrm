#pragma once
#include <string>
#include <utility>
#include "Creature.hpp"
#include "Tile.hpp"

class TileMovementConfirmation
{
  public:
    // bool = requires confirmation
    // string = confirmation message SID
    std::pair<bool, std::string> get_confirmation_details(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile);

  protected:
    std::pair<bool, std::string> check_for_jumping_into_water(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile);
};
