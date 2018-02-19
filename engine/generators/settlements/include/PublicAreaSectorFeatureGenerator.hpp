#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct PublicSectorFeatureType
{
  PUBLIC_SECTOR_FIRST = 0,
  PUBLIC_SECTOR_FEATURE_PARK = 0,
  PUBLIC_SECTOR_LAST = 0
};

class PublicAreaSectorFeatureGenerator : public SectorFeatureGenerator
{
  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx);
    bool generate_park(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    int get_min_feature_idx() const override;
    int get_max_feature_idx() const override;
};

