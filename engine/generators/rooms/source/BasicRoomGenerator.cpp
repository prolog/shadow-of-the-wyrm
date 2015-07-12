#include "BasicRoomGenerator.hpp"
#include "TileGenerator.hpp"

void BasicRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;

  for (int y = start_row; y < end_row; y++)
  {
    for (int x = start_col; x < end_col; x++)
    {
      TilePtr tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(y, x, tile);
    }
  }
}
