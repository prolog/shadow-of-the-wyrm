#pragma once
#include "SectorFeature.hpp"
#include "Building.hpp"

class PenSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    bool generate_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_sheep_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
};
