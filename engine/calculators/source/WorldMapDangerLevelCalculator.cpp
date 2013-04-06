#include <algorithm>
#include "CoordUtils.hpp"
#include "CreatureFeatures.hpp"
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
// The new map does not play into the calculations at all.
int WorldMapDangerLevelCalculator::calculate(MapPtr map, MapPtr new_map) const
{
  int danger_level = 0;

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
                      (static_cast<float>(max(world_dimensions.get_x(), world_dimensions.get_y()))));
      danger_level = (uint) danger_calc * CreatureConstants::MAX_CREATURE_LEVEL;
    }

    danger_level = max<int>(1, danger_level);
  }

  return danger_level;
}
