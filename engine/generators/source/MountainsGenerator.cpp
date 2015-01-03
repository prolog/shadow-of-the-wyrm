#include "MountainsGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

MountainsGenerator::MountainsGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_MOUNTAINS)
{
}

MapPtr MountainsGenerator::generate(const Dimensions& dimensions)
{
  TileGenerator tg;

  MapPtr result_map = std::make_shared<Map>(dimensions);
  Dimensions dim = result_map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int rand;
  TileType tile_type;
  TilePtr tile;
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      rand = RNG::range(1, 100);
      
      if (rand < 3)
      {
        TileType::TILE_TYPE = TileType::TILE_TYPE_TREE;
      }
      else if (rand < 5)
      {
        TileType::TILE_TYPE = TileType::TILE_TYPE_WEEDS;
      }
      else if (rand < 6)
      {
        TileType::TILE_TYPE = TileType::TILE_TYPE_BUSH;
      }
      else if (rand < 39)
      {
        TileType::TILE_TYPE = TileType::TILE_TYPE_CAIRN;
      }
      else if (rand < 53)
      {
        TileType::TILE_TYPE = TileType::TILE_TYPE_SCRUB;
      }
      else
      {
        TileType::TILE_TYPE = TileType::TILE_TYPE_FIELD;
      }
      
      tile = tg.generate(TileType::TILE_TYPE);
      result_map->insert(row, col, tile);
    }
  }
  
  return result_map;
}
