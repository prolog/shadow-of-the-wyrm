#pragma once
#include "Features.hpp"
#include "Generator.hpp"
#include "Map.hpp"

class GeneratorUtils
{
  public:
    // Generates a circle of a particular tile type using
    // Bresenham's circle algorithm.
    static void generate_circle(MapPtr map, const int row_centre, const int col_centre, const int radius, const TileType tile_type, const bool check_for_entirely_contained);

    // Generated a rounded rectangle.
    static void generate_rounded_rectangle(MapPtr map, const Coordinate& start, const int height, const int width, const TileType tile_type, const bool check_for_entirely_contained);

    // Generates a building: walls are TileType::TILE_TYPE_ROCK, floor is TileType::TILE_TYPE_DUNGEON.
    static void generate_building(const MapPtr map, const int start_row, const int start_col, const int height, const int width, const TileType tile_type = TileType::TILE_TYPE_ROCK, const TileType floor_type = TileType::TILE_TYPE_DUNGEON, const bool fancy_corners = false);
    
    // Generate a series of overlapping squares on a map to simulate a dug passage.
    static std::vector<std::pair<Coordinate, Coordinate>> generate_rectangles(const MapPtr map, const int start_row, const int start_col, const int end_row, const int end_col, const int num_rectangles, const TileType rect_fill_type);

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

    // Generates a bazaar somewhere on the map.
    static void generate_bazaar(const MapPtr map);

    // Generates a hermitage somewhere on the map.
    static void generate_hermitage(MapPtr map);

    // Generates a witchling's cottage somewhere on the map.
    static void generate_cottage(MapPtr map);

    // Generates a (possibly abandoned) surface mine on the map.
    static void generate_surface_mine(MapPtr map);

    // Generates storehouses of food over the map.
    static void generate_storehouses(MapPtr map);

    // Generates a random artifact and places it at a particular location.
    static void generate_randarts(MapPtr map, const Coordinate& c, const int num_randarts);
    static ItemPtr generate_randart();

    // Creates and item from the given list of IDs for each of the specified
    // coordinates.
    static void generate_item_per_coord(MapPtr map, const std::vector<Coordinate>& coords, const std::vector<std::string>& item_ids);

    // Fill a subset of the map with a certain tile type.
    static void fill(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const TileType tile_type);

    // Generate coastline on the map
    static void potentially_generate_coastline(MapPtr map, SOTW::Generator * const generator);
    static bool generate_coastline(MapPtr map, SOTW::Generator * const generator);

    static void add_random_stream_or_springs(MapPtr map, const int pct_chance_stream, const int pct_chance_springs);
    static void add_random_stream(MapPtr map);
    static void add_random_springs(MapPtr map);

    static std::vector<CardinalDirection> get_non_coastline_directions(SOTW::Generator* const gen);
    static void generate_dolmen(MapPtr map, SOTW::Generator * const gen);

    static bool generates_complexes(const TileType tt);

  protected:
    static bool position_in_range(const int min, const int max, const int actual);
    static bool are_tiles_ok_for_structure(MapPtr map, const int y_start, const int x_start, const int height, const int width);

    static const int STRUCTURE_NUM_ATTEMPTS;
    static const int STRUCTURE_MIN_WIDTH;
    static const int STRUCTURE_MAX_WIDTH;
    static const int STRUCTURE_MIN_HEIGHT;
    static const int STRUCTURE_MAX_HEIGHT;

    GeneratorUtils();
    ~GeneratorUtils();
};
