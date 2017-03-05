#include "DankRoomGenerator.hpp"
#include "TileGenerator.hpp"
#include "InscriptionTextKeys.hpp"
#include "RNG.hpp"

void DankRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;
  int val = 0;

  for (int y = start_row; y < end_row; y++)
  {
    for (int x = start_col; x < end_col; x++)
    {
      TilePtr tile;
      val = RNG::range(1, 100);

      if (val < 15)
      {
        tile = tg.generate(TileType::TILE_TYPE_BUSH);
      }
      else if (val < 35)
      {
        tile = tg.generate(TileType::TILE_TYPE_WEEDS);
      }
      else if (val < 50)
      {
        tile = tg.generate(TileType::TILE_TYPE_ROCKY_EARTH);
      }
      else
      {
        tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      
        if (tile != nullptr && RNG::x_in_y_chance(1, 400))
        {
          tile->set_inscription_sid(InscriptionTextKeys::get_random_inscription_sid());
        }
      }

      map->insert(y, x, tile);
    }
  }
}
