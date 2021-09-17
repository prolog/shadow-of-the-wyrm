#pragma once
#include "SectorFeature.hpp"
#include "Building.hpp"

enum struct PenContentsType
{
  PEN_CONTENTS_NONE = 0,
  PEN_CONTENTS_ANIMALS = 1,
  PEN_CONTENTS_VEGETABLES = 2,
  PEN_CONTENTS_WEEDS = 3
};

class PenSectorFeature : public SectorFeature
{
  public:
    PenSectorFeature(const PenContentsType new_contents = PenContentsType::PEN_CONTENTS_ANIMALS);

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    bool generate_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_animals_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_vegetables_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_weeds_to_pen(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    PenContentsType pen_contents;
};
