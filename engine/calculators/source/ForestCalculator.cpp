#include <cmath>
#include "ForestCalculator.hpp"

using namespace std;

map<TileType, int> ForestCalculator::fruit_probability_map;

ForestCalculator::ForestCalculator()
{
  if (fruit_probability_map.empty())
  {
    initialize_fruit_probability_map();
  }
}

void ForestCalculator::initialize_fruit_probability_map()
{
  fruit_probability_map.clear();

  fruit_probability_map.insert(make_pair(TileType::TILE_TYPE_WILD_ORCHARD, 10));
}

// Get the pct chance of a particular deciduous tree being a fruit tree
// in the given terrain type, returning 0 if the terrain type is not 
// present in the map.
int ForestCalculator::calculate_pct_chance_fruit(const TileType terrain_type)
{
  int pct_chance = 0;

  map<TileType, int>::iterator f_it = fruit_probability_map.find(terrain_type);

  if (f_it != fruit_probability_map.end())
  {
    pct_chance = f_it->second;
  }

  return pct_chance;
}

int ForestCalculator::calculate_pct_chance_deciduous(const int world_height, const Coordinate& world_loc)
{
  return (100 - calculate_pct_chance_evergreen(world_height, world_loc));
}

int ForestCalculator::calculate_pct_chance_evergreen(const int world_height, const Coordinate& world_loc)
{
  int pct_chance_evergreen = 0;

  int equator = (world_height / 2);
  double d_equator_normal = abs(static_cast<double>(world_loc.first) - equator) / equator;

  // No evergreens near the equator
  if (d_equator_normal > 0.2)
  {
    if (d_equator_normal < 0.45)
    {
      pct_chance_evergreen = static_cast<int>(100 * d_equator_normal / 4);
    }
    else if (d_equator_normal < 0.7)
    {
      pct_chance_evergreen = static_cast<int>(100 * d_equator_normal / 2);
    }
    else
    {
      pct_chance_evergreen = 50;
    }
  }

  return pct_chance_evergreen;
}

#ifdef UNIT_TESTS
#include "unit_tests/ForestCalculator_test.cpp"
#endif