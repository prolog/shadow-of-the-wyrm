#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct ResidentialSectorFeatureType
{
  RESIDENTIAL_SECTOR_FIRST = 0,
  RESIDENTIAL_SECTOR_FEATURE_ROCK_GARDEN = 0,
  RESIDENTIAL_SECTOR_FEATURE_FLOWER_GARDEN = 1,
  RESIDENTIAL_SECTOR_FEATURE_GARDEN = 2,
  RESIDENTIAL_SECTOR_LAST = 3
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

