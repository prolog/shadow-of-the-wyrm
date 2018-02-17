#pragma once
#include "SectorFeatureGenerator.hpp"

class DefaultSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};

