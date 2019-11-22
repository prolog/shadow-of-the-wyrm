#pragma once
#include "SectorFeature.hpp"

class ShrineSectorFeature : public SectorFeature
{
  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
    void generate_altar(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_building_features(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
};
