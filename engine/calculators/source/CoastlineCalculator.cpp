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
      pct_chance_kf = static_cast<int>(100 * d_equator_normal / 6);
    }
    else if (d_equator_normal < 0.90)
    {
      pct_chance_kf = static_cast<int>(100 * d_equator_normal / 4);
    }
  }

	return pct_chance_kf;
}

int CoastlineCalculator::calc_pct_chance_shoals() const
{
  return 40;
}

int CoastlineCalculator::generate_random_kelpforest_xiny_y() const
{
  return RNG::range(10, 100);
}

int CoastlineCalculator ::generate_random_shoals_xiny_y() const
{
  return RNG::range(20, 60);
}