#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct PublicSectorFeatureType
{
  PUBLIC_SECTOR_FIRST = 0,
  PUBLIC_SECTOR_FEATURE_SHOP = 0,
  PUBLIC_SECTOR_FEATURE_PLAZA = 1,
  PUBLIC_SECTOR_FEATURE_PARK = 2,
  PUBLIC_SECTOR_FEATURE_TOMB = 3,
  PUBLIC_SECTOR_FEATURE_GARDEN = 4,
  PUBLIC_SECTOR_LAST = 4
};

class PublicAreaSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    PublicAreaSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type);
    bool generate_plaza(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool generate_shop(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool generate_tomb(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    
    PublicSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, PublicSectorFeatureType> features;

};

