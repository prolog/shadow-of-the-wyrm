#pragma once
#include "SectorFeature.hpp"

class StorehouseSectorFeature : public SectorFeature
{
  public:
    StorehouseSectorFeature();
    virtual ~StorehouseSectorFeature() = default;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
};
