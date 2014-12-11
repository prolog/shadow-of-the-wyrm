#pragma once
#include "Directions.hpp"
#include "Map.hpp"
#include "Dimensions.hpp"
#include <set>
#include <utility>

//class MapComponents;
typedef std::vector<std::set<Coordinate>> MapComponents;
typedef std::vector<std::set<Coordinate>>::const_iterator MapComponentsItc;
typedef std::set<Coordinate> Component;
typedef std::set<Coordinate>::const_iterator ComponentItc;
typedef std::map<Direction, TilePtr> TileDirectionMap;
typedef std::map<Direction, CreaturePtr> CreatureDirectionMap;

class MapUtils
{
  public:    
    static MapComponents get_map_components(MapPtr map, const std::set<TileType>& exclusion_tiles);
    
    static bool add_or_update_location(MapPtr map, CreaturePtr creature, const Coordinate& new_coords, TilePtr creatures_old_tile = TilePtr() /* NULL by default*/);

    static Coordinate get_coordinate_for_creature(const MapPtr& map, const CreaturePtr& creature);
    static TilePtr get_tile_for_creature(const MapPtr& map, const CreaturePtr& creature);
    static uint get_num_following_creatures(const MapPtr& map);
    static TileDirectionMap get_adjacent_tiles_to_creature(const MapPtr& map, const CreaturePtr& creature);
    static TilePtr get_adjacent_tile(const MapPtr& map, const CreaturePtr& creature, const Direction d, const int offset = 1);
    static TileDirectionMap get_adjacent_and_creature_tiles(const MapPtr& map, const CreaturePtr& creature);
    static TileDirectionMap get_tiles_with_features(MapPtr& map, CreaturePtr& creature);
    static uint get_num_adjacent_creatures(const TileDirectionMap& adjacency_map);
    static CreatureDirectionMap get_adjacent_creatures(const MapPtr& map, const CreaturePtr& creature);
    static bool remove_creature(const MapPtr& map, const CreaturePtr& creature);

    static bool place_creature_randomly(MapPtr map, const std::string& creature_id);
    
    static bool can_exit_map(MapExitPtr map_exit);
    
    static bool is_blocking_feature_present(TilePtr tile);
    static bool is_creature_present(TilePtr tile);
    
    static bool is_tile_available_for_creature(CreaturePtr creature, TilePtr tile);
    static bool is_tile_available_for_item(TilePtr tile);
    
    static Dimensions get_dimensions(MapPtr map, const Coordinate& coords, const int size);
    
    static Coordinate convert_map_key_to_coordinate(const std::string& map_key);
    static std::string convert_coordinate_to_map_key(const Coordinate& c);
    static std::string convert_coordinate_to_map_key(const int row, const int col);
    
    static bool is_moving_from_land_type_tile_to_water_type_tile(TilePtr creatures_old_tile, TilePtr creatures_new_tile);
    
    static bool hostile_creature_exists(const std::string& creature_id_for_threat_check, MapPtr map);
    static bool adjacent_creature_exists(CreaturePtr creature, MapPtr map);
    static bool adjacent_creature_exists(const int row, const int col, MapPtr map);
    static bool adjacent_hostile_creature_exists(const std::string& creature_id_for_threat_check, MapPtr map);

    static void place_creature_on_previous_or_first_available_location(MapPtr map, CreaturePtr creature, const std::string& player_loc);
    
    // Check to see if the given tile is a "corner tile", given a corner direction.
    static bool is_corner(const Coordinate& c, const Direction d, MapPtr map);

    static bool are_coordinates_within_dimensions(const Coordinate& c, const Dimensions& d);

    // Create a distance map
    static std::multimap<int, std::pair<std::string, Coordinate>> create_distance_map(CreaturePtr creature, MapPtr map, bool hostile_only);

  protected: 
    static void add_connected_tiles_to_component(MapPtr map, const Coordinate& coord, const Dimensions& dim, const std::set<TileType>& exclusion_tiles, Component* component);
    static bool is_tile_contained_in_an_existing_component(const Coordinate&, const MapComponents& components);
};
