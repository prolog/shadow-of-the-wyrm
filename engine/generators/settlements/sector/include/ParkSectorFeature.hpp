#include "SectorFeature.hpp"

class ParkSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool should_generate_perimeter_statue(const int row, const int col, const Coordinate& start_coord, const Coordinate& end_coord, int row_cnt, int col_cnt);
};