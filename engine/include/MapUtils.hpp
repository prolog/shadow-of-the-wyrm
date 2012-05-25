#pragma once
#include "Directions.hpp"
#include "Map.hpp"
#include "Dimensions.hpp"
#include <set>
#include <utility>

//class MapComponents;
typedef std::vector<std::set<Coordinate> > MapComponents;
typedef std::vector<std::set<Coordinate> >::const_iterator MapComponentsItc;
typedef std::set<Coordinate> Component;
typedef std::set<Coordinate>::const_iterator ComponentItc;

class MapUtils
{
  public:
    // Check to see if the direction is a valid move.
    static bool is_valid_move(const Dimensions& dim, const Coordinate& c, const Direction d);
    
    // Get the direction of a move given the start and end coordinates.
    static Direction get_direction(const Coordinate& start_coord, const Coordinate& end_coord);

    // Get new coordinates.  "is_valid_move" should always be called first!
    static Coordinate get_new_coordinate(const Coordinate& c, const Direction d);

    static std::vector<Coordinate> get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col);
    static MapComponents get_map_components(MapPtr map, const std::set<TileType>& exclusion_tiles);
    
    static bool add_or_update_location(MapPtr map, CreaturePtr creature, const Coordinate& new_coords, TilePtr creatures_old_tile = TilePtr() /* NULL by default*/);

    static TilePtr get_tile_for_creature(const MapPtr& map, const CreaturePtr& creature);
    
    static bool can_exit_map(MapExitPtr map_exit);
    
    static bool is_blocking_feature_present(TilePtr tile);
    static bool is_creature_present(TilePtr tile);
    
    static int tile_distance_using_chebyshev(Coordinate c1, Coordinate c2);
    
    static bool is_tile_available_for_creature(TilePtr tile);
    
    static bool tile_type_permits_creature_or_object(const TileType tile_type);
    
    static Dimensions get_dimensions(MapPtr map, const Coordinate& coords, const int size);
    
    static bool are_coordinates_adjacent(const Coordinate& c1, const Coordinate& c2);

  protected: 
    static void add_connected_tiles_to_component(MapPtr map, const Coordinate& coord, const Dimensions& dim, const std::set<TileType>& exclusion_tiles, Component* component);
    static bool is_tile_contained_in_an_existing_component(const Coordinate&, const MapComponents& components);
};
