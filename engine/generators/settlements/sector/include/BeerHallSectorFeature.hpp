#pragma once
#include "SectorFeature.hpp"

class BeerHallSectorFeature : public SectorFeature
{
  public:
    // Beer halls can be generated in a variety of places.  If they're created
    // in a dungeon, we don't want to generate the actual building; if it's in
    // a city or town, we do.
    BeerHallSectorFeature();
    BeerHallSectorFeature(const bool generate_building_walls);

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    bool generate_walls;
};
