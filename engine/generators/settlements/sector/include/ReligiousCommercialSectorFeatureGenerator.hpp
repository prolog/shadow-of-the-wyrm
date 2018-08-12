#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct ReligiousCommercialSectorFeatureType
{
  RC_SECTOR_FIRST = 0,
  RC_SECTOR_FEATURE_ROCK_GARDEN = 0,
  RC_SECTOR_FEATURE_FLOWER_GARDEN = 1,
  RC_SECTOR_FEATURE_GARDEN = 2,
  RC_SECTOR_FEATURE_SHOP = 3,
  RC_SECTOR_FEATURE_OUTDOOR_SHRINE = 4,
  RC_SECTOR_LAST = 5
};

class ReligiousCommercialSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    ReligiousCommercialSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type);
    
    ReligiousCommercialSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, ReligiousCommercialSectorFeatureType> features;
};

