#pragma once
#include "Map.hpp"

// A class used to represent a sector feature in a city.  The generate
// function, given a map and coordinates, will generate the feature on
// the given coordinates.
class SectorFeature
{
  public:
    // Performs safety checks before generation.
    virtual bool generate(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

  protected:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) = 0;
};

using SectorFeaturePtr = std::unique_ptr<SectorFeature>;

