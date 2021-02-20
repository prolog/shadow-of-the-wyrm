#pragma once
#include "SectorFeature.hpp"
#include "Building.hpp"

class TavernSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
    void generate_barrels(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const Building& building);

    static const int MIN_HEIGHT_FOR_BARRELS;
};
