#include "BeehiveSectorFeature.hpp"
#include "CreatureFeatures.hpp"
#include "FeatureGenerator.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "RNG.hpp"

using namespace std;

const int BeehiveSectorFeature::PCT_CHANCE_ABANDONED_NEST = 10;

bool BeehiveSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool created = false;

  if (map != nullptr)
  {
    Coordinate c = CoordUtils::get_centre_coordinate(start_coord, end_coord);
    TilePtr tile = map->at(c);

    if (tile != nullptr && !tile->has_feature())
    {
      FeaturePtr hive_f;

      if (RNG::percent_chance(PCT_CHANCE_ABANDONED_NEST))
      {
        hive_f = FeatureGenerator::generate_hive();
      }
      else
      {
        hive_f = FeatureGenerator::generate_beehive();
      }

      tile->set_feature(hive_f);
      created = true;
    }
  }

  return created;
}
