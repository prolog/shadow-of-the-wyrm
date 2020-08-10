#pragma once
#include "SectorFeature.hpp"

class ParkSectorFeature : public SectorFeature
{
  public:
    ParkSectorFeature();
    ParkSectorFeature(const int pct_statues, const int pct_trader, const int pct_pond);

  protected:

    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool should_generate_perimeter_statue(const int row, const int col, const Coordinate& start_coord, const Coordinate& end_coord, int row_cnt, int col_cnt);

    const int pct_chance_statues;
    const int pct_chance_trader;
    const int pct_chance_pond;
};