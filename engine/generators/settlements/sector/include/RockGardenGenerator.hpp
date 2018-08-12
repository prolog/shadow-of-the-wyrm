#pragma once
#include "GardenSectorFeature.hpp"

class RockGardenGenerator : public GardenSectorFeature
{
  public:
    RockGardenGenerator(const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);

    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
