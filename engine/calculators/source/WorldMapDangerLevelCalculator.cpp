#include <algorithm>
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFeatures.hpp"
#include "DangerLevelProperties.hpp"
#include "GeneratorUtils.hpp"
#include "WorldMapDangerLevelCalculator.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;

// The danger level on the world map is defined to be:
// danger_(world) = ChebyshevDistance(current location, starting location)
//                 / (max(world map width, world map_height))
//                 * max_danger_level
// 
// min(1, danger_(world)) gives the final value.
//
// The new map only plays into the calculations if it's an underworld-type
// map.  Underworld maps whose type generates a complex (dungeon, sewers,
// mines) start off with a danger based on their current depth.
int WorldMapDangerLevelCalculator::calculate(MapPtr map, MapPtr new_map) const
{
  int danger_level = 0;
  string tile_type_s = get_property(DangerLevelProperties::DANGER_LEVEL_PROPERTIES_TILE_TYPE);

  if (!tile_type_s.empty())
  {
    TileType ttype = static_cast<TileType>(String::to_int(tile_type_s));

    if (GeneratorUtils::generates_complexes(ttype))
    {
      return 1;
    }
  }

  if (map)
  {
    Coordinate starting_location, current_location;

    Dimensions world_dimensions = map->size();

    starting_location = map->get_location(WorldMapLocationTextKeys::STARTING_LOCATION);
    current_location = map->get_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION);

    int distance = CoordUtils::chebyshev_distance(starting_location, current_location);

    if (distance > 0)
    {
      float danger_calc = (distance /
                          (static_cast<float>(get_max_distance(starting_location, map->size().get_y(), map->size().get_x()))));
      danger_level = static_cast<int>(danger_calc * CreatureConstants::MAX_CREATURE_LEVEL);
    }

    danger_level = max<int>(1, danger_level);
  }

  return danger_level;
}

int WorldMapDangerLevelCalculator::get_max_distance(const Coordinate& starting_location, const int map_max_y, const int map_max_x) const
{
  const int map_min_y = 0;
  const int map_min_x = 0;

  return std::max<int>({std::abs(starting_location.first - map_min_y),
                        std::abs(starting_location.first - map_max_y),
                        std::abs(starting_location.second - map_min_x),
                        std::abs(starting_location.second - map_max_x)});
}

#ifdef UNIT_TESTS
#include "unit_tests/WorldMapDangerLevelCalculator_test.cpp"
#endif

