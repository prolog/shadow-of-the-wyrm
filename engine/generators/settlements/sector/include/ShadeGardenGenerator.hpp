#pragma once
#include "GardenSectorFeature.hpp"

// Generates a shade garden: surrounded by trees, with shady plants
// and a bench in the centre.
class ShadeGardenGenerator : public GardenSectorFeature
{
  public:
    ShadeGardenGenerator(const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);
    virtual ~ShadeGardenGenerator() = default;

  protected:
    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    void generate_tree_cover(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_plants(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    void generate_features(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
};
