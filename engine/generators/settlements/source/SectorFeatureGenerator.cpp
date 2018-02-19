#include "SectorFeatureGenerator.hpp"
#include "RNG.hpp"

bool SectorFeatureGenerator::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  int feat_idx = RNG::range(get_min_feature_idx(), get_max_feature_idx());
  bool feature_generated = create_feature(map, start_coord, end_coord, feat_idx);

  return feature_generated;
}

