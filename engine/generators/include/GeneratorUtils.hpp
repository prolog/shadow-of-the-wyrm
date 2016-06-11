#pragma once
#include "Map.hpp"
#include "Trap.hpp"

class GeneratorUtils
{
  public:
    // Generates a circle of a particular tile type using
    // Bresenham's circle algorithm.
    static void generate_circle(MapPtr map, const int row_centre, const int col_centre, const int radius, const TileType tile_type);

    // Generates a building: walls are TileType::TILE_TYPE_ROCK, floor is TileType::TILE_TYPE_DUNGEON.
    static void generate_building(const MapPtr map, const int start_row, const int start_col, const int height, const int width);
    
    // Generates a TileType::TILE_TYPE_DUNGEON tile at the given coordinates, and places a Door feature on top of it.
    static void generate_door(const MapPtr map, const int row, const int col);
    
    // Generates a fire pillar feature on top of the existing tile.
    static void generate_fire_pillar(const MapPtr map, const int row, const int col);

    // Generates and returns a grave or barrow.  Graves are slightly more 
    // common than barrows.
    static TilePtr generate_grave_or_barrow();

    // Generates a Fountain feature on top of whatever tile exists at the current coordinates.
    static void generate_fountain(const MapPtr map, const int row, const int col);

    // Generates a given tile type at the given coordinates.
    static void generate_tile(const MapPtr map, const int row, const int col, const TileType tile_type);
    
    // Generates a number of random traps over the map.
    // Return value is number of traps generated.
    static int generate_traps(const MapPtr map, const int num_traps);

    // Generates a particular trap at the given coordinate.
    static void generate_trap(const MapPtr map, const int row, const int col, const std::vector<TrapPtr>& traps, const std::string& trap_id, const bool trap_triggered = false);

    // Generates a random trap from the game at the given coordinates.
    static void generate_trap(const MapPtr map, const int row, const int col, const std::vector<TrapPtr>& traps, const bool trap_triggered = false);

  protected:
    static bool position_in_range(const int min, const int max, const int actual);
    
    GeneratorUtils();
    ~GeneratorUtils();
};
