#pragma once
#include "SectorFeature.hpp"

class ShopSectorFeature : public SectorFeature
{
  public:
    virtual ~ShopSectorFeature() = default;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
