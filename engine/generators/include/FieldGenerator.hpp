#pragma once

#include "Generator.hpp"

class FieldGenerator : public Generator
{
  public:
    virtual MapPtr generate(const Dimensions& dimensions, const std::string& map_exit_id);

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);
};
