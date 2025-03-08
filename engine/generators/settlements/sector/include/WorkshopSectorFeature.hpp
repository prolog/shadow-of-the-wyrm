#pragma once
#include "SectorFeature.hpp"

class WorkshopSectorFeature : public SectorFeature
{
  public:
    WorkshopSectorFeature();
    virtual ~WorkshopSectorFeature() = default;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    int growth_rate;
};
