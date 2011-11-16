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

  // JCD FIXME: Class should probably be made static at some point.
  public:
    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim) = 0;

  protected:
    virtual void fill(const MapPtr map, const TileType& tile_type);
};

typedef boost::shared_ptr<Generator> GeneratorPtr;
