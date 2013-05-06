#pragma once

#include "Generator.hpp"

class FieldGenerator : public SL::Generator
{
  public:
    FieldGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dimensions);

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);
};
