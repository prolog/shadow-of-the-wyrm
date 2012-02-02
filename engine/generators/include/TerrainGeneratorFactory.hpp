#pragma once
#include "Generator.hpp"
#include "tiles.hpp"

class TerrainGeneratorFactory
{
  public:
    static GeneratorPtr create_generator(const TileType terrain_type);

  protected:
    TerrainGeneratorFactory();
    ~TerrainGeneratorFactory();
};
