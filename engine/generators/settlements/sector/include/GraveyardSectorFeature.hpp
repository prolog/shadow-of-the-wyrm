#pragma once
#include "SectorFeature.hpp"

class GraveyardSectorFeature : public SectorFeature
{
  public:
    virtual ~GraveyardSectorFeature() = default;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
