#pragma once
#include "SectorFeature.hpp"
#include "Building.hpp"
#include "EntranceState.hpp"

enum struct EnclosureContentsType
{
  ENCLOSURE_CONTENTS_NONE = 0,
  ENCLOSURE_CONTENTS_ANIMALS = 1,
  ENCLOSURE_CONTENTS_VEGETABLES = 2,
  ENCLOSURE_CONTENTS_WEEDS = 3
};

class EnclosureSectorFeature : public SectorFeature
{
  public:
    virtual ~EnclosureSectorFeature() = default;

    EnclosureSectorFeature(const EnclosureContentsType new_contents = EnclosureContentsType::ENCLOSURE_CONTENTS_ANIMALS);

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    bool generate_enclosure(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const EntranceStateType est);
    bool add_animals(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_vegetables(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    bool add_weeds(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    EnclosureContentsType pen_contents;
};
