#pragma once
#include <vector>
#include "common.hpp"
#include "ISeason.hpp"
#include "Map.hpp"
#include "RarityTypes.hpp"

class Dimensions;

// Need the namespace to disambiguate from boost's generators - apparently, MSVC
// doesn't like the unqualified name...
namespace SOTW
{
  class Generator
  {  
    #ifdef UNIT_TESTS
    friend class GeneratorTest;
    #endif

    public:
      Generator(const std::string& new_map_exit_id, TileType new_map_terrain_type);
      virtual ~Generator() = default;

      // Generate the map and its contents (creatures, features, items, etc.)
      virtual MapPtr generate_and_initialize(const int danger_level);
      virtual MapPtr generate_and_initialize(const int danger_level, const Depth& depth);
      virtual MapPtr generate_and_initialize(const int danger_level, const Dimensions& dim);
   
      virtual MapPtr generate();
      virtual MapPtr generate(const Dimensions& dim) = 0;
      virtual void   create_entities(MapPtr map, const int danger_level, const bool generate_creatures = true, const bool generate_items = true);
   
      virtual void set_terrain_type(const TileType new_map_terrain_type);
      virtual TileType get_terrain_type() const;

      virtual std::pair<bool, bool> override_depth_update_defaults() const;

      // Whether or not to create initial items - this will be true for a select
      // few generators (dungeons and caverns), and false for all others.
      virtual bool can_create_initial_items() const;
   
      // Additional properties, which can be keyed in on by the actual subclasses of Generator.
      virtual void clear_additional_properties();
      virtual void set_additional_property(const std::string& property_name, const std::string& property_value);
      virtual void set_additional_properties(const std::map<std::string, std::string>& additional_properties);
      virtual bool has_additional_property(const std::string& property_name) const;
      virtual std::string get_additional_property(const std::string& property_name) const;
      
      // For each property with "RECURSIVE" at the end, strip off "RECURSIVE"
      // and find that property in the additional properties, returning it as
      // part of a map.  Also include the "RECURSIVE" properties themselves,
      // so that they can be populated into future generators.
      virtual std::map<std::string, std::string> get_recursive_properties() const;

      // Each property that starts with "<number>_DEPTH_" is a depth-specific
      // property.  These are copied forward and backward to ensure that the
      // maps at the specific depth always have the necessary properties.
      virtual std::map<std::string, std::string> get_depth_properties() const;

      // Generator filters are used to generate creatures - creatures who match
      // the tile type and all the generator filters are included when considering
      // the set of creatures to generate.
      virtual std::vector<std::string> get_generator_filters() const;

      virtual ExitMovementType get_last_exit_movement_type() const;
      virtual bool get_place_on_down_staircase(const ExitMovementType emt) const;

      virtual void add_feature_entry_text_sid(const std::string& new_sid);
      virtual void set_feature_entry_text_sids(const std::vector<std::string>& new_feature_entry_text_sids);
      virtual void clear_feature_entry_text_sids();

      virtual MapType get_map_type() const;

      virtual bool get_allow_ancient_beasts() const;

    protected:
   
      virtual void generate_additional_structures(MapPtr map);

      virtual void generate_shipwreck(MapPtr map, const Coordinate& shipwreck_coord, const std::vector<std::string>& addl_items, const int min_lore);
      virtual void generate_treasure(MapPtr map);
      virtual void generate_treasure_on_coords(MapPtr map, const std::vector<Coordinate>& treasure_coords, const int min_lore);
      virtual void generate_randarts(MapPtr map, int y, int x, int min_lore);

      virtual void set_map_permanence(MapPtr map);
      virtual bool get_permanence() const; // Check additional properties, and only then check the default
      virtual bool get_permanence_default() const;
      virtual void update_map_permanence_from_additional_properties(MapPtr map);
      virtual void update_depth_details(MapPtr map);

      virtual void initialize(MapPtr map, const int danger_level);
      virtual void fill(const MapPtr map, const TileType& tile_type);
      virtual void fill(const MapPtr map, const std::vector<std::pair<TileType, int>>& tiles);
      virtual bool place_staircase(MapPtr current_map, const int row, const int col, const TileType tile_type, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location, const std::string& extra_desc = "");
      virtual bool place_up_staircase(MapPtr current_map, const int row, const int col, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location, const std::string& extra_desc = "");
      virtual bool place_down_staircase(MapPtr current_map, const int row, const int col, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location, const std::string& extra_desc = "");
      virtual void add_tile_exit(MapPtr map, const Coordinate& c, const Direction direction, const bool link_to_map_exit);
      virtual void set_custom_map_linkage_for_depth(TilePtr tile, const Direction exit_direction, const Depth& depth, const std::string& linkback_map_id);
      virtual void set_depth_custom_map_id_properties(TilePtr tile);
      virtual void update_custom_map_with_current(const std::string& depth_map_id, const Direction direction, const std::string& linkback_map_id, const Depth& new_depth);
    
      // Seed the initial items.  Returns true if the items were created, false otherwise.
      virtual bool generate_initial_items(MapPtr map, const int danger_level, const std::tuple<bool, int, Rarity>& creature_details);
      virtual bool update_items(MapPtr map, const int danger_level);
      virtual bool generate_foragables(MapPtr map, const ForagableType ft);
      virtual std::map<TileType, std::vector<std::string>> get_foragables_for_season(ISeason*, const ForagableType ft);

      virtual bool get_ignore_creature_generation_level_checks() const;
      virtual void create_properties_and_copy_to_map(MapPtr map);
      virtual void set_property_to_generator_and_map(MapPtr map, const std::string& property, const std::string& value);
      virtual void set_depth_properties_to_map(MapPtr map);

      virtual bool does_tile_lead_to_previous_map(const MapType map_type, const TileType tile_type, const Depth& depth);
      std::string map_exit_id;
      TileType map_terrain_type;
      int danger_level;
      std::map<std::string, std::string> additional_properties;

      // Displayed when the player enters a map for the first time.  Room messages, basically.
      std::vector<std::string> feature_entry_text_sids; 

      // JCD FIXME: If I ever go with larger maps, these could be divisors.
      static const int FORAGABLE_MIN;
      static const int FORAGABLE_MAX;
      
      static const std::string RECURSIVE_PROPERTY_SUFFIX;
      static const std::string DEPTH_PROPERTY_PREFIX;
  };
}

using GeneratorPtr = std::unique_ptr<SOTW::Generator>;
