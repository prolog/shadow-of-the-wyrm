#include "OverworldMapDangerLevelCalculator.hpp"

// The danger for an overworld map is calculated by getting the current
// danger for the given map.  This calculator is likely to be infrequently
// used - most cases will involve the WorldMap generator (generating the
// danger for a new Overworld or Underworld map, given the current World
// map), or the Underworld generator (generating the danger for the next/
// previous dungeon or cavern level).
//
// The new map doesn't get used at all for the overworld calculations.
uint OverworldMapDangerLevelCalculator::calculate(MapPtr map, MapPtr new_map) const
{
  uint danger_level = 0;

  if (map)
  {
    danger_level = map->get_danger();
  }
  
  return danger_level;
}

#ifdef UNIT_TESTS
#include "unit_tests/OverworldMapDangerLevelCalculator_test.cpp"
#endif

