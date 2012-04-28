#include "MountainsGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

MountainsGenerator::MountainsGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id)
{
}

MapPtr MountainsGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = MapPtr(new Map(dimensions));
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
        tile_type = TILE_TYPE_TREE;
      }
      else if (rand < 5)
      {
        tile_type = TILE_TYPE_WEEDS;
      }
      else if (rand < 6)
      {
        tile_type = TILE_TYPE_BUSH;
      }
      else if (rand < 39)
      {
        tile_type = TILE_TYPE_CAIRN;
      }
      else if (rand < 53)
      {
        tile_type = TILE_TYPE_SCRUB;
      }
      else
      {
        tile_type = TILE_TYPE_FIELD;
      }
      
      tile = TileGenerator::generate(tile_type);
      result_map->insert(row, col, tile);
    }
  }
  
  return result_map;
}
