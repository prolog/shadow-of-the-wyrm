#pragma once
#include "BoundingBox.hpp"
#include "Directions.hpp"
#include "Map.hpp"
#include "Dimensions.hpp"
#include <set>
#include <utility>

using MapComponents = std::vector<std::set<Coordinate>>;
using MapComponentsItc = std::vector<std::set<Coordinate>>::const_iterator;
using Component = std::set<Coordinate>;
using ComponentItc = std::set<Coordinate>::const_iterator;
using TileDirectionMap = std::map<Direction, TilePtr>;
using CreatureDirectionMap = std::map<Direction, CreaturePtr>;

class MapUtils
{
  public:    
    static MapComponents get_map_components(MapPtr map, const std::set<TileType>& exclusion_tiles);
    
    static bool add_or_update_location(MapPtr map, CreaturePtr creature, const Coordinate& new_coords, TilePtr creatures_old_tile = nullptr);

    static std::vector<std::string> get_creatures_with_creature_in_view(const MapPtr& map, const std::string& creature_id);
    static Coordinate get_coordinate_for_creature(const MapPtr& map, const CreaturePtr& creature);
    static TilePtr get_tile_for_creature(const MapPtr& map, const CreaturePtr& creature);
    static uint get_num_following_creatures(const MapPtr& map);
    static TileDirectionMap get_available_adjacent_tiles_to_creature(const MapPtr& map, const CreaturePtr& tiles_around_creature, const CreaturePtr& creature_to_place);
    static TileDirectionMap get_adjacent_tiles_to_creature(const MapPtr& map, const CreaturePtr& creature);
    static std::vector<TilePtr> get_adjacent_tiles_to_creature_unsorted(const MapPtr& map, const CreaturePtr& creature, const int offset = 1);
    static bool adjacent_tiles_match_type(const MapPtr& map, const Coordinate& c, const std::vector<Direction>& directions, const TileType tile_type_to_match);
    static uint get_num_adjacent_movement_directions(const MapPtr& map, const CreaturePtr& creature);
    static TilePtr get_adjacent_tile(const MapPtr& map, const CreaturePtr& creature, const Direction d, const int offset = 1);
    static TileDirectionMap get_adjacent_and_creature_tiles(const MapPtr& map, const CreaturePtr& creature);
    static TileDirectionMap get_tiles_with_features(MapPtr& map, CreaturePtr& creature);
    static uint get_num_adjacent_creatures(const TileDirectionMap& adjacency_map);
    static CreatureDirectionMap get_adjacent_creatures(const MapPtr& map, const CreaturePtr& creature);
    static std::vector<CreaturePtr> get_adjacent_creatures_unsorted(const MapPtr& map, const CreaturePtr& creature);
    static void set_up_transitive_exits_as_necessary(MapPtr old_map, MapExitPtr map_exit);
    static Coordinate calculate_new_coord_for_multimap_movement(const Coordinate& current_coord, const Direction exit_direction, MapExitPtr map_exit);
    static Direction get_exit_direction(const Direction d, const Dimensions& dim, const Coordinate& c);

    // When removing a creature, we generally want to leave the player's
    // location intact, for returning later.  However, in certain cases,
    // we want to remove the player fully, e.g., when hiding and removing
    // the player from a calculated FOV map.
    static bool remove_creature(const MapPtr& map, const CreaturePtr& creature, const bool force_player_removal = false);
    static bool tiles_in_range_match_type(MapPtr map, const BoundingBox& bb, const TileType tt);

    static bool place_creature_randomly(MapPtr map, const std::string& creature_id);
    
    static bool can_exit_map(MapPtr map, CreaturePtr creature, MapExitPtr map_exit, const Coordinate& proposed_new_coord);
    
    static bool is_blocking_feature_present(TilePtr tile);
    static bool is_creature_present(TilePtr tile);
    
    static std::pair<bool, std::string> is_in_shop_or_adjacent(MapPtr map, const Coordinate& c);

    static bool does_area_around_tile_allow_creature_generation(MapPtr map, const Coordinate& c);
    static bool is_tile_available_for_creature(CreaturePtr creature, TilePtr tile);
    static bool is_tile_available_for_item(TilePtr tile);
    static bool does_area_around_tile_contain_staircase(MapPtr map, const Coordinate& c);
    static bool is_coordinate_within_player_restricted_zone(MapPtr map, const Coordinate& c);

    static void swap_places(MapPtr map, CreaturePtr c1, CreaturePtr c2);

    static bool can_squeeze_by(MapPtr map, CreaturePtr c1, const Coordinate& adjacent_creature_coords, const Direction d);
    static bool squeeze_by(MapPtr map, CreaturePtr c1, const Coordinate& adjacent_creature_coords, const Direction d);
    
    static Dimensions get_dimensions(MapPtr map, const Coordinate& coords, const int size);
    
    static Coordinate convert_map_key_to_coordinate(const std::string& map_key);
    static std::string convert_coordinate_to_map_key(const Coordinate& c);
    static std::string convert_coordinate_to_map_key(const int row, const int col);
    
    static bool is_moving_from_land_type_tile_to_water_type_tile(TilePtr creatures_old_tile, TilePtr creatures_new_tile);
    
    static bool hostile_creature_exists(const std::string& creature_id_for_threat_check, MapPtr map);
    static std::vector<CreaturePtr> get_hostile_creatures(const std::string& creature_id_for_threat_check, MapPtr map);
    static bool are_creatures_adjacent(MapPtr map, CreaturePtr c1, CreaturePtr c2);
    static bool adjacent_creature_exists(CreaturePtr creature, MapPtr map);
    static bool adjacent_creature_exists(const int row, const int col, MapPtr map);
    static bool adjacent_hostile_creature_exists(const std::string& creature_id_for_threat_check, MapPtr map);

    static Coordinate place_creature(MapPtr map, CreaturePtr creature, const std::string& player_loc, const Coordinate& linked_location);
    static void set_multi_map_entry_details(MapPtr new_map, MapPtr old_map, const Coordinate& new_map_prev_loc);

    // Check to see if the given tile is a "corner tile", given a corner direction.
    static bool is_corner(const Coordinate& c, const Direction d, MapPtr map);

    static bool are_coordinates_within_dimensions(const Coordinate& c, const Dimensions& d);

    // Create a distance map
    static std::multimap<int, std::pair<std::string, Coordinate>> create_distance_map(CreaturePtr creature, MapPtr map, bool hostile_only);

    static std::map<TileType, std::vector<TilePtr>> partition_tiles(MapPtr map);
    static std::vector<TilePtr> get_tiles_supporting_items(MapPtr map);

    static void anger_shopkeeper_if_necessary(const Coordinate& current_coords, MapPtr current_map, CreaturePtr anger_creature);

    static void calculate_fov_maps_for_all_creatures(MapPtr map);

    static int calculate_depth_delta(MapPtr map, TilePtr tile, const ExitMovementType emt);

    static bool should_link_entry_point(const MapType map_type);

    // Weather is per-tile on the world map, per-map on overworld maps,
    // non-existant elsewhere.
    static WeatherPtr get_weather(MapPtr map, TilePtr tile);

    static bool is_intersection(MapPtr map, CreaturePtr cr, const Coordinate& c);
    static std::vector<std::string> place_followers(MapPtr map, CreaturePtr cr, const Coordinate& c);
    static void serialize_and_remove_followers(MapPtr map, CreaturePtr creature);

    // Returns true for the first parameter if a melee attack at range is
    // possible, false otherwise. The second parameter will be populated
    // with a valid tile if the first parameter is true.
    static std::pair<bool, TilePtr> get_melee_attack_target(MapPtr map, CreaturePtr creature, const Direction d);

    static std::string get_map_description(MapPtr map);
    static std::vector<CardinalDirection> get_unblocked_door_dirs(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord);

  protected: 
    static void add_connected_tiles_to_component(MapPtr map, const Coordinate& coord, const Dimensions& dim, const std::set<TileType>& exclusion_tiles, Component* component);
    static bool is_tile_contained_in_an_existing_component(const Coordinate&, const MapComponents& components);

    static void add_tile_related_messages(CreaturePtr creature, TilePtr tile, const bool is_world_map);
    static bool add_message_about_tile_if_necessary(CreaturePtr creature, TilePtr tile, const bool is_world_map);
    static bool add_message_about_items_on_tile_if_necessary(CreaturePtr creature, TilePtr tile);
    static void run_movement_scripts(CreaturePtr creature, const std::string& map_id, const Coordinate& c);

    static const int PLAYER_RESTRICTED_ZONE_RADIUS;
};
