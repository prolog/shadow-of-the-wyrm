#pragma once
#include "SectorFeature.hpp"

class LibrarySectorFeature : public SectorFeature
{
  public:
    LibrarySectorFeature();

    bool generate_interior(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const Coordinate& door_coord);

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};

class LittleLibrarySectorFeature : public SectorFeature
{
  public:
    LittleLibrarySectorFeature();

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
