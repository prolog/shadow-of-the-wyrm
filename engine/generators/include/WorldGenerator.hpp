#pragma once
#include <map>
#include <set>
#include "CellularAutomataTypes.hpp"
#include "Generator.hpp"

// JCD FIXME: Eventually, set about changing all the "MapPtr" arguments to "const MapPtr&" arguments.

class WorldGenerator : public Generator
{
  public:
    WorldGenerator();
    WorldGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual MapPtr generate_set_islands_and_continents(MapPtr map);
    virtual MapPtr generate_random_islands(MapPtr map);
    virtual void   generate_village_surroundings(MapPtr map);

    virtual void populate_terrain_cell_maps(const Dimensions& dimensions, CellMap& field_cell_map, CellMap& forest_cell_map, CellMap& mountains_cell_map, CellMap& marsh_cell_map, CellMap& scrub_cell_map, CellMap& desert_cell_map);
    
    virtual void process_field_cell(MapPtr map, const int row, const int col, const CellValue cv);
    virtual void process_marsh_cell(MapPtr map, const int row, const int col, const CellValue marsh_val, const CellValue field_val);
    virtual void process_forest_cell(MapPtr map, const int row, const int col, const CellValue forest_val, const CellValue field_val);
    virtual void process_desert_cell(MapPtr map, const int row, const int col, const CellValue desert_val, const CellValue scrub_val, const CellValue field_val);
    virtual void process_scrub_cell(MapPtr map, const int row, const int col, const CellValue scrub_val, const CellValue field_val);
    virtual void process_mountain_cell(MapPtr map, const int row, const int col, const CellValue mountains_val, const CellValue forest_val, const CellValue field_val);

    void generate_little_island(MapPtr map);
    void generate_far_reaches(MapPtr map);
    
    void populate_race_information();
    void set_village_races(MapPtr map);
    void remove_village_coordinates_if_present(const Coordinate& c);
    
    std::set<Coordinate> village_coordinates;
    std::set<std::string> unused_initial_race_ids;
};
