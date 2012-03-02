#pragma once

#include "Generator.hpp"

class ForestGenerator : public Generator
{
  public:
    ForestGenerator();
    ForestGenerator(const int pct_chance_stream, const int pct_chance_springs);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dimensions, const std::string& map_exit_id);

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);
    virtual MapPtr add_random_bushes_and_weeds(MapPtr map);
    virtual MapPtr add_random_stream_or_springs(MapPtr map);
    virtual MapPtr add_random_stream(MapPtr map);
    virtual MapPtr add_random_springs(MapPtr map);

    const int PCT_CHANCE_FOREST_STREAM;
    const int PCT_CHANCE_FOREST_SPRINGS;
};
