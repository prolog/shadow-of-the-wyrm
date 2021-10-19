#pragma once
#include "SectorFeature.hpp"

class StorehouseSectorFeature : public SectorFeature
{
  public:
    StorehouseSectorFeature();

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
};
