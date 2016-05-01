#pragma once
#include "Creature.hpp"
#include "Map.hpp"

class Game;

// Class containing useful utilities for the Game class that don't need
// to clutter up the Game class itself.
class GameUtils
{
  public:
    // Make the current map permanent.  Note that this function assumes the map
    // is a regular map generated randomly off a world map tile (a forest, a field,
    // etc).
    static void make_map_permanent(Game& game, CreaturePtr creature, MapPtr current_map);
    static void add_new_creature_to_map(Game& game, CreaturePtr new_creature, MapPtr map, const Coordinate& coords);
    static bool is_creature_in_player_view_map(Game& game, const std::string& creature_id);
    static bool is_creature_adjacent(Game& game, CreaturePtr creature1, CreaturePtr creature2);
    static double get_seconds(Game& game);

    static bool is_player_among_creatures(CreaturePtr creature1, CreaturePtr creature2);

  protected:
    GameUtils();
};

