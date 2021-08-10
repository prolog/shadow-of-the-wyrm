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
    LittleLibrarySectorFeature(const bool new_generate_walls, const int new_danger_level = DEFAULT_DANGER_LEVEL);
    
    void set_danger_level(const int new_danger_level);
    int get_danger_level() const;

    int get_default_danger_level() const;

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    bool generate_walls;
    int danger_level;

    static const int DEFAULT_DANGER_LEVEL;
};
