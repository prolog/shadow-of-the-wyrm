#pragma once
#include "SectorFeature.hpp"

class BeerHallSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
