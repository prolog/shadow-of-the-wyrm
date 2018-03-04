#include "SectorFeature.hpp"
#include "CoordUtils.hpp"

using namespace std;

bool SectorFeature::generate(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map && CoordUtils::is_in_range(map->size(), start_coord, end_coord))
  {
    generated = generate_feature(map, start_coord, end_coord);
  }

  return generated;
}

