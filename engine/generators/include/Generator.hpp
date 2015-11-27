#pragma once
#include <vector>
#include "common.hpp"
#include "Map.hpp"
#include "RarityTypes.hpp"

class Dimensions;

// Need the namespace to disambiguate from boost's generators - apparently, MSVC
// doesn't like the unqualified name...
namespace SL
{
  class Generator
  {  
    #ifdef UNIT_TESTS
    friend class GeneratorTest;
    #endif

    public:
      Generator(const std::string& new_map_exit_id, TileType new_map_terrain_type);

      // Generate the map and its contents (creatures, features, items, etc.)
      virtual MapPtr generate_and_initialize(const int danger_level);
      virtual MapPtr generate_and_initialize(const int danger_level, const Depth& depth);
      virtual MapPtr generate_and_initialize(const int danger_level, const Dimensions& dim);
   
      virtual MapPtr generate();
      virtual MapPtr generate(const Dimensions& dim) = 0;
      virtual void   create_entities(MapPtr map, const int danger_level, const bool generate_creatures = true, const bool generate_items = true);
   
      virtual void set_terrain_type(const TileType new_map_terrain_type);
      virtual TileType get_terrain_type() const;

      // Whether or not to create initial items - this will be true for a select
      // few generators (dungeons and caverns), and false for all others.
      virtual bool can_create_initial_items() const;
   
      // Additional properties, which can be keyed in on by the actual subclasses of Generator.
      virtual void clear_additional_properties();
      virtual void set_additional_property(const std::string& property_name, const std::string& property_value);
      virtual void set_additional_properties(const std::map<std::string, std::string>& additional_properties);
      virtual bool has_additional_property(const std::string& property_name) const;
      virtual std::string get_additional_property(const std::string& property_name) const;

      // Generator filters are used to generate creatures - creatures who match
      // the tile type and all the generator filters are included when considering
      // the set of creatures to generate.
      virtual std::vector<std::string> get_generator_filters() const;

      virtual MapType get_map_type() const;

  protected:

      virtual void set_map_permanence(MapPtr map);
      virtual bool get_permanence() const; // Check additional properties, and only then check the default
      virtual bool get_permanence_default() const;
      virtual void update_map_permanence_from_additional_properties(MapPtr map);

      virtual void initialize(MapPtr map, const int danger_level);
      virtual void fill(const MapPtr map, const TileType& tile_type);
      virtual bool place_staircase(MapPtr current_map, const int row, const int col, const TileType tile_type, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location);
      virtual void add_tile_exit(MapPtr map, const Coordinate& c, const Direction direction, const bool link_to_map_exit);
      virtual void set_custom_map_id_for_depth(TilePtr tile, const Direction exit_direction, const Depth& depth, const std::string& linkback_map_id);
      virtual void set_depth_custom_map_id_properties(TilePtr tile);
      virtual void update_custom_map_with_current(const std::string& depth_map_id, const Direction direction, const std::string& linkback_map_id, const Depth& new_depth);
    
      // Seed the initial items.  Returns true if the items were created, false otherwise.
      virtual bool generate_initial_items(MapPtr map, const int danger_level, const std::tuple<bool, int, Rarity>& creature_details);
      virtual bool update_items(MapPtr map, const int danger_level);

      virtual bool get_ignore_creature_generation_level_checks() const;
      virtual void create_properties_and_copy_to_map(MapPtr map);
      virtual void set_property_to_generator_and_map(MapPtr map, const std::string& property, const std::string& value);

      std::string map_exit_id;
      TileType map_terrain_type;
      int danger_level;
      std::map<std::string, std::string> additional_properties;

      // Displayed when the player enters a map for the first time.  Room messages, basically.
      std::vector<std::string> feature_entry_text_sids; 
  };
}

using GeneratorPtr = std::shared_ptr<SL::Generator>;
