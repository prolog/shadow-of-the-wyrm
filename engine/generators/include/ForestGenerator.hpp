#pragma once
#include "Generator.hpp"
#include "ForestCalculator.hpp"

class ForestGenerator : public SOTW::Generator
{
  public:
    ForestGenerator(const std::string& map_exit_id);
    ForestGenerator(const int pct_chance_stream, const int pct_chance_springs);
    virtual ~ForestGenerator() = default;

    virtual MapPtr generate() override;
    virtual MapPtr generate(const Dimensions& dimensions) override;

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);
    virtual void add_random_bushes_and_weeds(MapPtr map, const int pct_chance_evergreen);
    virtual TilePtr generate_tree_based_on_world_location(const int world_map_height, const Coordinate& world_location, const int pct_chance_evergreen);

    const int PCT_CHANCE_FOREST_STREAM;
    const int PCT_CHANCE_FOREST_SPRINGS;

    ForestCalculator fc;
};
