#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct ResidentialSectorFeatureType
{
  RESIDENTIAL_SECTOR_FIRST = 0,
  RESIDENTIAL_SECTOR_FEATURE_GRAVES = 0,
  RESIDENTIAL_SECTOR_FEATURE_ROCK_GARDEN = 1,
  RESIDENTIAL_SECTOR_FEATURE_FLOWER_GARDEN = 2,
  RESIDENTIAL_SECTOR_FEATURE_GARDEN = 3,
  RESIDENTIAL_SECTOR_FEATURE_SHOP = 4,
  RESIDENTIAL_SECTOR_FEATURE_SHRINE = 5,
  RESIDENTIAL_SECTOR_FEATURE_HOUSE = 6,
  RESIDENTIAL_SECTOR_FEATURE_WORKSHOP = 7,
  RESIDENTIAL_SECTOR_LAST = 8
};

class ResidentialSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    ResidentialSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type);
    
    ResidentialSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, ResidentialSectorFeatureType> features;
};

