#pragma once
#include "SectorFeature.hpp"

class SurfaceMineSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
    void generate_mine(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void add_excavated_dirt(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_creatures(MapPtr map, std::vector<Coordinate>& available_coords);

    static const int PCT_CHANCE_INHABITED;
};
