#pragma once
#include "Generator.hpp"

class ScrubGenerator : public Generator
{
  public:
    virtual MapPtr generate(const Dimensions& dim, const std::string& map_exit_id);

  protected:
    virtual TilePtr generate_tile(MapPtr result_map, const int row, const int col);
};
