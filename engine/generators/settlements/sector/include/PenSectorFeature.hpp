#pragma once
#include "SectorFeature.hpp"
#include "Building.hpp"

enum struct PenContentsType
{
  PEN_CONTENTS_ANIMALS = 0,
  PEN_CONTENTS_VEGETABLES = 1,
  PEN_CONTENTS_WEEDS = 2
};

class PenSectorFeature : public SectorFeature
{
  protected:
    PenSectorFeature(const PenContentsType new_contents = PenContentsType::PEN_CONTENTS_ANIMALS);

    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    bool generate_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_animals_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_vegetables_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_weeds_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    PenContentsType pen_contents;
};
