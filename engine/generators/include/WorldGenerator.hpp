#pragma once
#include <future>
#include <map>
#include <set>
#include <vector>
#include "CellularAutomataTypes.hpp"
#include "CreatureGenerationIndex.hpp"
#include "Generator.hpp"
#include "Random.hpp"
#include "TileDepthOptions.hpp"
#include "TileGenerator.hpp"

// Asynchronous version of world generation, intended to be passed to a thread.
// Calls generate().  Necessary because of SDL and event queues - without this
// running asynchronously, the window goes "Not Responding".
void async_worldgen(std::promise<MapPtr>&& mp);

// JCD FIXME: Eventually, set about changing all the "MapPtr" arguments to "const MapPtr&" arguments.

class WorldGenerator : public SOTW::Generator
{
  public:
    WorldGenerator();
    WorldGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate() override;
    virtual MapPtr generate(const Dimensions& dim) override;

    virtual void   set_village_coordinates(MapPtr map);
    virtual void   set_treasure(MapPtr map);

  protected:
    virtual MapType get_map_type() const override;
    virtual MapPtr generate_random_islands(MapPtr map);
    virtual void   generate_village_surroundings(MapPtr map);

    virtual void populate_terrain_cell_maps(const Dimensions& dimensions, CellMap& field_cell_map, CellMap& forest_cell_map, CellMap& hills_cell_map, CellMap& mountains_cell_map, CellMap& marsh_cell_map, CellMap& scrub_cell_map, CellMap& desert_cell_map);
    
    virtual void process_field_cell(MapPtr map, const int row, const int col, const CellValue cv);
    virtual void process_hill_cell(MapPtr map, const int row, const int col, const CellValue hill_val, const CellValue field_val);
    virtual void process_marsh_cell(MapPtr map, const int row, const int col, const CellValue marsh_val, const CellValue field_val);
    virtual void process_forest_cell(MapPtr map, const int row, const int col, const CellValue forest_val, const CellValue field_val);
    virtual void process_desert_cell(MapPtr map, const int row, const int col, const CellValue desert_val, const CellValue scrub_val, const CellValue field_val);
    virtual void process_scrub_cell(MapPtr map, const int row, const int col, const CellValue scrub_val, const CellValue field_val);
    virtual void process_mountain_cell(MapPtr map, const int row, const int col, const CellValue mountains_val, const CellValue forest_val, const CellValue field_val);

    virtual void post_process_cell(MapPtr map, const int row, const int col);
    void potentially_add_properties(const int row, const int col, TilePtr tile, const std::vector<std::pair<int, std::pair<std::string, std::string>>>& prop_pairs);

    void populate_race_information();
    void set_village_races(MapPtr map);
    void remove_village_coordinates_if_present(const Coordinate& c);
    void set_tile_properties(TilePtr tile, TileType tile_type, const int row, const int col);
    TilePtr generate_feature_or_default(const std::vector<std::pair<int, std::pair<TileType, TileType>>>& special_features, TileType default_tile_type, const int row, const int col);
    
    void set_initial_creatures_for_village(TilePtr village_tile, const std::string& village_race_id);
    std::vector<std::string> get_potential_creatures(const std::string& village_race_id);
    void set_creatures_to_village_tile(TilePtr tile, const std::vector<std::string>& potential_creature_ids);
    
    // Set all the various tile depth information.
    void set_tile_depth_details(TilePtr tile);

    // Set the tile depth
    void set_tile_depth_options(TilePtr tile, TileDepthOptions& tdo, int& max_depth);

    // Set creature details for the depth (ie, what's the engraving of?)
    void set_tile_depth_creature_details(TilePtr tile, const int max_depth);

    // Tile-specific property setup functions.
    void set_dungeon_complex_properties(TilePtr tile);
    void set_castle_properties(TilePtr tile);
    void set_keep_properties(TilePtr tile);
    void set_sewer_complex_properties(TilePtr tile);

    std::string get_race_village_extra_description_sid(const std::string& race_id);

    void potentially_add_treasure(const std::string& map_key, TilePtr tile, NormalDistribution& treasure_difficulty, bool& terrain_override);

    // A map containing pointers to member functions - used to set up special
    // sets of properties on particular tile types.
    std::map<TileType, void (WorldGenerator::*)(TilePtr tile)> tile_property_fns;

    // Used to set min/max depths for underworld tile types.
    std::map<TileType, TileDepthOptions> tile_depth_options;

    std::set<Coordinate> village_coordinates;
    std::set<std::string> initial_race_ids;
    std::map<std::string, std::string> village_race_sids;

    TileGenerator tg;
    std::unordered_map<TileType, CreatureGenerationIndex> creature_generation_map_cache;

    static const int MIN_CREATURES_PER_VILLAGE;
    static const int MAX_CREATURES_PER_VILLAGE;
    static const int MAX_DANGER_LEVEL_FOR_WORLD_GEN;
    static const pair<int, int> X_IN_Y_CHANCE_TREASURE;
};
