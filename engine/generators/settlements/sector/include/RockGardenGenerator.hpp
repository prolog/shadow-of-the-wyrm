#pragma once
#include "SectorFeature.hpp"

class RockGardenGenerator : public SectorFeature
{
  public:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
