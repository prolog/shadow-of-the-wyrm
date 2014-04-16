#include "CryptGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

CryptGenerator::CryptGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_CRYPT)
{
}

MapPtr CryptGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(dim);
  fill(map, TILE_TYPE_ROCK);
  
  // ...
   
  return map;
}

TilePtr CryptGenerator::generate_tile(MapPtr current_map, const int row, const int col)
{
  TilePtr grave_tile = tg.generate(TILE_TYPE_CRYPT);

  return grave_tile;
}

bool CryptGenerator::get_permanence_default() const
{
  return true;
}

