#pragma once
#include "SectorFeatureGenerator.hpp"
#include "SectorFeatureTypes.hpp"

class LowIncomeResidentialSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    LowIncomeResidentialSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type);
    
    LowIncomeResidentialSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, LowIncomeResidentialSectorFeatureType> features;
};

