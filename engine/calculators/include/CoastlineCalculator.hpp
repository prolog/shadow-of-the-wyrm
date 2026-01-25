#pragma once
#include "Generator.hpp"

class CoastlineCalculator
{
  public:
    int calc_pct_chance_kelp_forest(const std::pair<Coordinate, int>& world_map_location_and_height) const;
    int calc_pct_chance_shoals() const;
    int generate_random_kelpforest_xiny_y() const;
    int generate_random_shoals_xiny_y() const;
};

