#include "BeehiveSectorFeature.hpp"
#include "FeatureGenerator.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "RNG.hpp"

using namespace std;

const int BeehiveSectorFeature::PCT_CHANCE_ABANDONED_NEST = 10;
const string BeehiveSectorFeature::BEEHIVE_DRONE_ID = "_bee";

bool BeehiveSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool created = false;

  if (map != nullptr)
  {
    Coordinate c = CoordUtils::get_centre_coordinate(start_coord, end_coord);
    TilePtr tile = map->at(c);

    if (tile != nullptr && !tile->has_feature())
    {
      FeaturePtr hive_f = FeatureGenerator::generate_hive();

      if (!RNG::percent_chance(PCT_CHANCE_ABANDONED_NEST))
      {
        // Populate the hive
        shared_ptr<Hive> hive = std::dynamic_pointer_cast<Hive>(hive_f);

        if (hive != nullptr)
        {
          const CreatureMap& creatures = Game::instance().get_creatures_ref();
          auto cr_it = creatures.find(BEEHIVE_DRONE_ID);

          if (cr_it != creatures.end())
          {
            hive->populate_from(cr_it->second);
          }
        }
      }

      tile->set_feature(hive_f);
      created = true;
    }
  }

  return created;
}
