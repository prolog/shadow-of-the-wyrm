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
   Generator(const std::string& new_map_exit_id): map_exit_id(new_map_exit_id) {};
   virtual MapPtr generate();
   virtual MapPtr generate(const Dimensions& dim) = 0;
   
  protected:
    virtual void fill(const MapPtr map, const TileType& tile_type);
    std::string map_exit_id;
};

typedef boost::shared_ptr<Generator> GeneratorPtr;
