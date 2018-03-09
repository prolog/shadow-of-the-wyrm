#include "SectorFeature.hpp"

class TombSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
    std::vector<CardinalDirection> decorate_corners(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    static const int MIN_TOMB_HEIGHT;
    static const int MIN_TOMB_WIDTH;
};
