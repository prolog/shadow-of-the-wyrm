#pragma once
#include "Generator.hpp"

class MarshGenerator : public Generator
{
  public:
    MarshGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);
    virtual MapPtr  add_random_trees_bushes_weeds_and_reeds(MapPtr current_map);
};
