#pragma once
#include "SectorFeature.hpp"

class TombSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
    std::vector<Direction> decorate_corners(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_opening(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const std::vector<Direction>& potential_door_locations);
    void generate_grave(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_bones_and_treasure(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    static const int MIN_TOMB_HEIGHT;
    static const int MIN_TOMB_WIDTH;
};
