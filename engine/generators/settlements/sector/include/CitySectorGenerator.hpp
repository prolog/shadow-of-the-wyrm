#pragma once
#include "CitySectorTypes.hpp"
#include "Map.hpp"

class CitySectorGenerator
{
  public:
    bool generate_feature(MapPtr map, const Coordinate& start, const Coordinate& end, const CitySectorType sector_type, const int sector_feature_type);
};

