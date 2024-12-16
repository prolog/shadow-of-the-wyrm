#include "WetRoomGenerator.hpp"
#include "TileGenerator.hpp"
#include "InscriptionTextKeys.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"

WetRoomGenerator::WetRoomGenerator()
{
  pct_chance_wet = RNG::range(40, 60);
}

void WetRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;
  map->set_property(MapProperties::MAP_PROPERTIES_WET, std::to_string(true));

  for (int y = start_row; y < end_row; y++)
  {
    for (int x = start_col; x < end_col; x++)
    {
      TilePtr tile;
      
      if (RNG::percent_chance(pct_chance_wet))
      {
        tile = tg.generate(TileType::TILE_TYPE_RIVER);
      }
      else if (RNG::percent_chance((100 - pct_chance_wet) / 2))
      {
        tile = tg.generate(TileType::TILE_TYPE_REEDS);
      }
      else
      {
        tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      }

      map->insert(y, x, tile);
    }
  }
}
