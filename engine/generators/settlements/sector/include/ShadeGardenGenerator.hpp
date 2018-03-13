#pragma once
#include "SectorFeature.hpp"

// Generates a shade garden: surrounded by trees, with shady plants
// and a bench in the centre.
class ShadeGardenGenerator : public SectorFeature
{
  protected:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    void generate_tree_cover(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_plants(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_features(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
};
