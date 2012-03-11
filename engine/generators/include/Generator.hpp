#pragma once

#include <vector>
#include "common.hpp"
#include "Map.hpp"

class Dimensions;

class Generator
{  
  #ifdef UNIT_TESTS
  friend class GeneratorTest;
  #endif

  public:
   virtual MapPtr generate(const std::string& map_id = "");
   virtual MapPtr generate(const Dimensions& dim, const std::string& map_exit_id) = 0;
   
  protected:
    virtual void fill(const MapPtr map, const TileType& tile_type);
    std::string map_exit_id;
};

typedef boost::shared_ptr<Generator> GeneratorPtr;
