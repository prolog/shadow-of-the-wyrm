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
    FruitVegetableGardenGenerator(const FruitVegetableGardenType fvg = FruitVegetableGardenType::FVG_TYPE_VEGETABLE, const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, const int new_col_spacing = 3, const int new_row_spacing = 2, const bool new_has_fence = false);

    void set_has_fence(const bool new_has_fence);
    bool get_has_fence() const;

  protected:
    void populate_vegetable_map();
    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    std::map<int, std::string> vegetable_map;
    int vegetable_min;
    int vegetable_max;
    FruitVegetableGardenType fv_type;
    int col_spacing;
    int row_spacing;
    bool has_fence;
};

class OrchardGenerator : public FruitVegetableGardenGenerator
{
  public:
    OrchardGenerator();

    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;
};
