#include "WetRoomGenerator.hpp"
#include "TileGenerator.hpp"
#include "InscriptionTextKeys.hpp"
#include "RNG.hpp"

WetRoomGenerator::WetRoomGenerator()
{
  pct_chance_wet = RNG::range(40, 80);
}

void WetRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;

  for (int y = start_row; y < end_row; y++)
  {
    for (int x = start_col; x < end_col; x++)
    {
      TilePtr tile;
      
      if (RNG::percent_chance(pct_chance_wet))
      {
        tile = tg.generate(TileType::TILE_TYPE_RIVER);
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
