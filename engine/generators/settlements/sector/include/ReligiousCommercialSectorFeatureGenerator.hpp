#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct ReligiousCommercialSectorFeatureType
{
  LIR_SECTOR_FIRST = 0,
  LIR_SECTOR_FEATURE_GARDEN = 0,
  LIR_SECTOR_LAST = 1
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

