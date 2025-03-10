#pragma once
#include "SectorFeature.hpp"

class PlazaSectorFeature : public SectorFeature
{
  public:
    virtual ~PlazaSectorFeature() = default;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    static const int MIN_PLAZA_FOUNTAIN_HEIGHT;
    static const int MIN_PLAZA_FOUNTAIN_WIDTH;
};
