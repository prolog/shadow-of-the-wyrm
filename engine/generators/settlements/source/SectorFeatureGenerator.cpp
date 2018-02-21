#include "SectorFeatureGenerator.hpp"
#include "RNG.hpp"

bool SectorFeatureGenerator::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  int feat_idx = RNG::range(1, 100);
  bool feature_generated = create_feature(map, start_coord, end_coord, feat_idx);

  return feature_generated;
}

