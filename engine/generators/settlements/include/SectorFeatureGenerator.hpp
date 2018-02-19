#pragma once
#include "Map.hpp"

class SectorFeatureGenerator
{
  public:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

  protected:
    virtual bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feature_idx) = 0;

    virtual int get_min_feature_idx() const = 0;
    virtual int get_max_feature_idx() const = 0;
};

using SectorFeatureGeneratorPtr = std::shared_ptr<SectorFeatureGenerator>;
