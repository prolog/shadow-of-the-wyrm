#pragma once
#include "Map.hpp"

class SectorFeatureGenerator
{
  public:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_type);

  protected:
    virtual bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feature_idx, const int feat_type) = 0;
};

using SectorFeatureGeneratorPtr = std::shared_ptr<SectorFeatureGenerator>;
