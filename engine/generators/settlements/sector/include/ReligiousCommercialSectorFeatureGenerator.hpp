#pragma once
#include "SectorFeatureGenerator.hpp"
#include "SectorFeatureTypes.hpp"

class ReligiousCommercialSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    ReligiousCommercialSectorFeatureGenerator();
    virtual ~ReligiousCommercialSectorFeatureGenerator() = default;

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type);
    
    ReligiousCommercialSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, ReligiousCommercialSectorFeatureType> features;
};

