#pragma once
#include "Generator.hpp"
#include "tiles.hpp"

class TerrainGeneratorFactory
{
  public:
    static GeneratorPtr create_generator(const std::string& map_exit_id, const TileType terrain_type, const TileType terrain_subtype = TILE_TYPE_UNDEFINED);

  protected:
    TerrainGeneratorFactory();
    ~TerrainGeneratorFactory();
};
