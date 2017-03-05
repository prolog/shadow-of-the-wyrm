#include "CaveInRoomGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

CaveInRoomGenerator::CaveInRoomGenerator()
{
  pct_chance_cave_in = RNG::range(70, 90);
}

void CaveInRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;
  bool can_generate_solid_rock = false;
  TilePtr tile;

  for (int y = start_row; y < end_row; y++)
  {
    for (int x = start_col; x < end_col; x++)
    {
      can_generate_solid_rock = (y > start_row && y < (end_row - 1) && x > start_col && (x < (end_col - 1)));

      if (can_generate_solid_rock && RNG::percent_chance(pct_chance_cave_in))
      {
        tile = tg.generate(TileType::TILE_TYPE_ROCK);
      }
      else
      {
        tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      }

      map->insert(y, x, tile);
    }
  }
}
