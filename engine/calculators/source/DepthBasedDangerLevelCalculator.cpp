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
      int new_map_cur_depth = new_map_depth.get_current();
      int delta = calculate_delta(map_depth, new_map_depth);

      if (is_more_dangerous(delta, new_map_cur_depth))
      {
        delta = std::abs(delta);
      }
      else
      {
        delta = std::abs(delta) * -1;
      }

      danger_level += delta;
    }
  }

  return danger_level;
}

bool DepthBasedDangerLevelCalculator::is_more_dangerous(const int delta, const int cur_depth) const
{
  bool more_danger = false;
  
  // Above ground
  if (cur_depth < 0)
  {
    if (delta < 0)
    {
      more_danger = true;
    }
  }
  // Below ground
  else
  {
    if (delta > 0)
    {
      more_danger = true;
    }
  }

  return more_danger;
}

int DepthBasedDangerLevelCalculator::calculate_delta(const Depth& map_depth, const Depth& new_map_depth) const
{
  int delta = 0;

  int cur = map_depth.get_current();

  // The new map depth is considered authoritative in terms of min/max depths,
  // so use that to default the current depth appropriately if it's outside
  // the min or max.
  if (cur > new_map_depth.get_maximum())
  {
    cur = new_map_depth.get_maximum();
  }
  else if (cur < new_map_depth.get_minimum())
  {
    cur = new_map_depth.get_minimum();
  }

  delta = new_map_depth.get_current() - cur;
  return delta;
}

#ifdef UNIT_TESTS
#include "unit_tests/DepthBasedDangerLevelCalculator_test.cpp"
#endif

