#include "WetRoomGenerator.hpp"
#include "TileGenerator.hpp"
#include "InscriptionTextKeys.hpp"
#include "MapProperties.hpp"
#include "MushRoomGenerator.hpp"
#include "RNG.hpp"

const int WetRoomGenerator::PCT_CHANCE_MUSHROOMS = 65;

WetRoomGenerator::WetRoomGenerator()
{
  pct_chance_wet = RNG::range(40, 60);
}

void WetRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;
  map->set_property(MapProperties::MAP_PROPERTIES_WET, std::to_string(true));
  MushRoomGenerator mrg(true);
  bool mushrooms = RNG::percent_chance(PCT_CHANCE_MUSHROOMS);
  bool this_tile_mushrooms = false;
  TilePtr tile;

  for (int y = start_row; y < end_row; y++)
  {
    for (int x = start_col; x < end_col; x++)
    {
      this_tile_mushrooms = false;
      
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
        this_tile_mushrooms = mushrooms && true;
      }

      map->insert(y, x, tile);

      // If we need to add mushrooms, do so after the tile has been
      // inserted so it can be retrieved by the MushRoomGenerator.
      if (this_tile_mushrooms)
      {
        mrg.generate(map, y, y + 1, x, x + 1);
      }
    }
  }
}
