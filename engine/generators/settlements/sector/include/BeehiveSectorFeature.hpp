#pragma once
#include "SectorFeature.hpp"
#include "SectorFeatureTypes.hpp"

class BeehiveSectorFeature : public SectorFeature
{
  public:
    virtual ~BeehiveSectorFeature() = default;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    static const int PCT_CHANCE_ABANDONED_NEST;
};

