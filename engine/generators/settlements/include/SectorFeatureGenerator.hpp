#pragma once
#include "Map.hpp"

class SectorFeatureGenerator
{
  public:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) = 0;
};

using SectorFeatureGeneratorPtr = std::shared_ptr<SectorFeatureGenerator>;
