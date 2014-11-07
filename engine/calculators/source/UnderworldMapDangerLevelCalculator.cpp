#include "UnderworldMapDangerLevelCalculator.hpp"

using namespace std;

// Calculate the danger level for an underworld map.  This is the base
// danger level, +/- the delta in depth.
int UnderworldMapDangerLevelCalculator::calculate(MapPtr map, MapPtr new_map) const
{
  int danger_level = 0;

  if (map)
  {
    danger_level = map->get_danger();

    if (new_map)
    {
      Depth map_depth = map->size().depth();
      Depth new_map_depth = new_map->size().depth();

      danger_level += (new_map_depth.get_current() - map_depth.get_current());
    }
  }

  return danger_level;
}

#ifdef UNIT_TESTS
#include "unit_tests/UnderworldMapDangerLevelCalculator_test.cpp"
#endif

