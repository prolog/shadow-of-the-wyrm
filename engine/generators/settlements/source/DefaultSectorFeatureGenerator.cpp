#include "DefaultSectorFeatureGenerator.hpp"

bool DefaultSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx)
{
  return false;
}

int DefaultSectorFeatureGenerator::get_min_feature_idx() const
{
  return 0;
}

int DefaultSectorFeatureGenerator::get_max_feature_idx() const
{
  return 0;
}

