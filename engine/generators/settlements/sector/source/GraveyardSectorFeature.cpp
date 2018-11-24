#include "GraveyardSectorFeature.hpp"
#include "GraveyardGenerator.hpp"
#include "OrderedGraveyardGenerator.hpp"
#include "RNG.hpp"
#include "ScatteredGraveyardGenerator.hpp"

using namespace std;

bool GraveyardSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    shared_ptr<GraveyardGenerator> gg;
    string map_id = map->get_map_id();

    if (RNG::percent_chance(50))
    {
      gg = std::make_shared<OrderedGraveyardGenerator>(map_id);
    }
    else
    {
      gg = std::make_shared<ScatteredGraveyardGenerator>(map_id);
    }

    gg->generate(map, start_coord, end_coord);
  }

  return generated;
}

