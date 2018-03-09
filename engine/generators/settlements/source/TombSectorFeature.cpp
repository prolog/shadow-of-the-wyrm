#include "TombSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int TombSectorFeature::MIN_TOMB_HEIGHT = 5;
const int TombSectorFeature::MIN_TOMB_WIDTH = 5;

bool TombSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    int width = CoordUtils::get_width(start_coord, end_coord);
    int height = CoordUtils::get_height(start_coord, end_coord);

    if (width >= MIN_TOMB_WIDTH && height >= MIN_TOMB_HEIGHT)
    {
      GeneratorUtils::fill(map, start_coord, end_coord, TileType::TILE_TYPE_ROCK);
      GeneratorUtils::fill(map, make_pair(start_coord.first + 2, start_coord.second + 2), make_pair(end_coord.first - 2, end_coord.second - 2), TileType::TILE_TYPE_DUNGEON);
      generated = true;
    }

    vector<CardinalDirection> potential_door_locations = decorate_corners(map, start_coord, end_coord);


  }

  return generated;
}

vector<CardinalDirection> TombSectorFeature::decorate_corners(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  // first = N corners decorated
  // second = S corners decorated
  vector<CardinalDirection> door_locs;

  if (map != nullptr)
  {
    vector<Coordinate> corners;
    TileGenerator tg;

    // Potential chance to "round the corners".
    if (RNG::percent_chance(50))
    {
      corners.push_back(start_coord);
      corners.push_back(make_pair(start_coord.first, end_coord.second));
      door_locs.push_back(CardinalDirection::CARDINAL_DIRECTION_NORTH);
    }

    if (RNG::percent_chance(50))
    {
      corners.push_back(make_pair(end_coord.first, start_coord.second));
      corners.push_back(end_coord);
      door_locs.push_back(CardinalDirection::CARDINAL_DIRECTION_SOUTH);
    }

    for (const Coordinate& c : corners)
    {
      TilePtr tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(c, tile);
    }
  }

  if (door_locs.empty())
  {
    door_locs.push_back(CardinalDirection::CARDINAL_DIRECTION_SOUTH);
  }

  return door_locs;
 }
