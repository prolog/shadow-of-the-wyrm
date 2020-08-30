#pragma once
#include "GardenSectorFeature.hpp"

class FruitVegetableGardenGenerator : public GardenSectorFeature
{
  public:
    FruitVegetableGardenGenerator(const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);

  protected:
    void populate_vegetable_map();
    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    std::map<int, std::string> vegetable_map;
    int vegetable_min;
    int vegetable_max;
};
