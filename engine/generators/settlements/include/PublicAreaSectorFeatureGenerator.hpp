#pragma once
#include "SectorFeatureGenerator.hpp"

enum struct PublicSectorFeatureType
{
  PUBLIC_SECTOR_FIRST = 0,
  PUBLIC_SECTOR_FEATURE_SHOP = 0,
  PUBLIC_SECTOR_FEATURE_PLAZA = 1,
  PUBLIC_SECTOR_FEATURE_PARK = 2,
  PUBLIC_SECTOR_LAST = 2
};

class PublicAreaSectorFeatureGenerator : public SectorFeatureGenerator
{
  public:
    PublicAreaSectorFeatureGenerator();

  protected:
    bool create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx);
    bool generate_park(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool generate_plaza(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool generate_shop(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    
    bool should_generate_perimeter_statue(const int row, const int col, const Coordinate& start_coord, const Coordinate& end_coord, int row_cnt, int col_cnt);

    PublicSectorFeatureType get_random_feature(const int feat_idx) const;
    std::map<int, PublicSectorFeatureType> features;

    static const int MIN_PLAZA_FOUNTAIN_HEIGHT;
    static const int MIN_PLAZA_FOUNTAIN_WIDTH;
};

