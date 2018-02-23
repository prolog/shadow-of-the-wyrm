#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct PublicSectorFeatureType
{
  PUBLIC_SECTOR_FIRST = 0,
  PUBLIC_SECTOR_FEATURE_SHOP = 0,
  PUBLIC_SECTOR_FEATURE_PARK = 1,
  PUBLIC_SECTOR_LAST = 1
};

class PublicAreaSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    PublicAreaSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx);
    bool generate_park(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool generate_shop(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    PublicSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, PublicSectorFeatureType> features;
};

