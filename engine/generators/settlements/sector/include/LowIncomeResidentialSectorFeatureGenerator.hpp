#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct LowIncomeResidentialSectorFeatureType
{
  LIR_SECTOR_FIRST = 0,
  LIR_SECTOR_FEATURE_HOUSE = 0,
  LIR_SECTOR_FEATURE_GRAVES = 1,
  LIR_SECTOR_FEATURE_VEGETABLE_GARDEN = 2,
  LIR_SECTOR_FEATURE_ROCK_GARDEN = 3,
  LIR_SECTOR_FEATURE_SHOP = 4,
  LIR_SECTOR_FEATURE_BEER_HALL = 5,
  LIR_SECTOR_FEATURE_WORKSHOP = 6,
  LIR_SECTOR_LAST = 7
};

class LowIncomeResidentialSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    LowIncomeResidentialSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type);
    bool generate_house(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    
    LowIncomeResidentialSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, LowIncomeResidentialSectorFeatureType> features;
};

