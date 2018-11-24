#include "RockGardenGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

RockGardenGenerator::RockGardenGenerator(const string& new_deity_id, const AlignmentRange new_ar)
: GardenSectorFeature(new_deity_id, new_ar)
{
}

bool RockGardenGenerator::generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  TileGenerator tg;

  for (int row = start_coord.first; row <= end_coord.first; row++)
  {
    for (int col = start_coord.second; col <= end_coord.second; col++)
    {
      // 80% chance of Cairn, 20% chance of field
      TilePtr tile = tg.generate(RNG::percent_chance(80) ? TileType::TILE_TYPE_CAIRN : TileType::TILE_TYPE_FIELD);

      map->insert(row, col, tile);
    }
  }

  return true;
}
