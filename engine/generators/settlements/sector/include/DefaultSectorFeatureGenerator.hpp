#pragma once
#include "SectorFeatureGenerator.hpp"

class DefaultSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    virtual ~DefaultSectorFeatureGenerator() = default;

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type) override;
};

