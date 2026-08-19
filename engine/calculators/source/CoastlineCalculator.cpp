#include "CoastlineCalculator.hpp"
#include "RNG.hpp"

using namespace std;

int CoastlineCalculator::calc_pct_chance_kelp_forest(const pair<Coordinate, int>& world_map_location_and_height) const
{
	int pct_chance_kf = 0;
	int equator = (world_map_location_and_height.second / 2);
	double d_equator_normal = abs(static_cast<double>(world_map_location_and_height.first.first) - equator) / equator;

  // Kelp forests appear in more temperate and arctic areas.
  if (d_equator_normal > 0.3)
  {
    if (d_equator_normal < 0.65)
    {
      pct_chance_kf = static_cast<int>(100 * d_equator_normal / 5);
    }
    else if (d_equator_normal < 0.90)
    {
      pct_chance_kf = static_cast<int>(100 * d_equator_normal / 3);
    }
  }

	return pct_chance_kf;
}

int CoastlineCalculator::calc_pct_chance_shoals() const
{
  // Consistent across the world. (the oceans are shallow?)
  return 40;
}

int CoastlineCalculator::generate_random_kelpforest_xiny_y() const
{
  return RNG::range(10, 100);
}

int CoastlineCalculator::generate_random_shoals_xiny_y() const
{
  return RNG::range(20, 60);
}

int CoastlineCalculator::calc_pct_chance_shoals(const vector<TileType>& adjacent_tile_types) const
{
  int pct_chance_shoals = 0;

  for (const TileType att : adjacent_tile_types)
  {
    if (att == TileType::TILE_TYPE_MOUNTAINS)
    {
      pct_chance_shoals += 10;
    }
    else if (att == TileType::TILE_TYPE_HILLS)
    {
      pct_chance_shoals += 7;
    }
    else if (att == TileType::TILE_TYPE_MARSH)
    {
      pct_chance_shoals += 5;
    }
    else if (att == TileType::TILE_TYPE_FIELD  || 
             att == TileType::TILE_TYPE_FOREST || 
             att == TileType::TILE_TYPE_SCRUB  ||
             att == TileType::TILE_TYPE_DESERT)
    {
      pct_chance_shoals += 1;
    }
  }

  return std::min<int>(pct_chance_shoals, 100);
}

#ifdef UNIT_TESTS
#include "unit_tests/CoastlineCalculator_test.cpp"
#endif
