#pragma once
#include "GardenSectorFeature.hpp"

enum struct FruitVegetableGardenType
{
  FVG_TYPE_FRUIT = 0,
  FVG_TYPE_VEGETABLE = 1
};

class FruitVegetableGardenGenerator : public GardenSectorFeature
{
  public:
    FruitVegetableGardenGenerator(const FruitVegetableGardenType fvg = FruitVegetableGardenType::FVG_TYPE_VEGETABLE, const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);

  protected:
    void populate_vegetable_map();
    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    std::map<int, std::string> vegetable_map;
    int vegetable_min;
    int vegetable_max;
    FruitVegetableGardenType fv_type;
};

class OrchardGenerator : public FruitVegetableGardenGenerator
{
  public:
    OrchardGenerator();

    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
