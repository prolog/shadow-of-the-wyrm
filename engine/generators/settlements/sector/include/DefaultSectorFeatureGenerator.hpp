#pragma once
#include "SectorFeatureGenerator.hpp"

class DefaultSectorFeatureGenerator : public SectorFeatureGenerator
{
  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx) override;
};

