#include "SectorFeatureGenerator.hpp"
#include "RNG.hpp"

bool SectorFeatureGenerator::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int f_type)
{
  int feat_idx = RNG::range(1, 100);
  bool feature_generated = create_feature(map, start_coord, end_coord, feat_idx, f_type);

  return feature_generated;
}

