#include "DepthBasedDangerLevelCalculator.hpp"

using namespace std;

DepthBasedDangerLevelCalculator::DepthBasedDangerLevelCalculator(const ExitMovementType new_emt)
: emt(new_emt)
{
}

// Calculate the danger level for any map dependent on depth (underworld,
// certain overworld).  This is the base danger level, +/- the delta in depth.
int DepthBasedDangerLevelCalculator::calculate(MapPtr map, MapPtr new_map) const
{
  int danger_level = 0;

  if (map)
  {
    danger_level = map->get_danger();

    if (new_map)
    {
      Depth map_depth = map->size().depth();
      Depth new_map_depth = new_map->size().depth();
      int delta = new_map_depth.get_current() - map_depth.get_current();

      // Ensure that if we're ascending on an overworld map (new depth < 0)
      // that it gets *more* dangerous.  Think of this as climbing a tower,
      // with more and more dangerous creatures the higher one goes.
      if (delta < 0 && new_map_depth.get_current() < 0 && emt == ExitMovementType::EXIT_MOVEMENT_ASCEND)
      {
        delta *= -1;
      }

      danger_level += delta;
    }
  }

  return danger_level;
}

#ifdef UNIT_TESTS
#include "unit_tests/DepthBasedDangerLevelCalculator_test.cpp"
#endif

