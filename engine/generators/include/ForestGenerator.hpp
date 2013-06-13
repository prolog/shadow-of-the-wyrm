#pragma once

#include "Generator.hpp"
#include "ForestCalculator.hpp"

class ForestGenerator : public SL::Generator
{
  public:
    ForestGenerator(const std::string& map_exit_id);
    ForestGenerator(const int pct_chance_stream, const int pct_chance_springs);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dimensions);

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);
    virtual MapPtr add_random_bushes_and_weeds(MapPtr map);
    virtual MapPtr add_random_stream_or_springs(MapPtr map);
    virtual MapPtr add_random_stream(MapPtr map);
    virtual MapPtr add_random_springs(MapPtr map);
    virtual TilePtr generate_tree_based_on_world_location(const int world_map_height, const Coordinate& world_location, const int pct_chance_evergreen);

    const int PCT_CHANCE_FOREST_STREAM;
    const int PCT_CHANCE_FOREST_SPRINGS;

    ForestCalculator fc;
};
