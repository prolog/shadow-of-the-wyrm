#pragma once
#include "Generator.hpp"

class ScrubGenerator : public Generator
{
  public:
    ScrubGenerator(const std::string& map_exit_id);
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual TilePtr generate_tile(MapPtr result_map, const int row, const int col);
};
