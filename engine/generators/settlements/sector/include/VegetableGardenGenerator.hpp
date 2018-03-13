#pragma once
#include "SectorFeature.hpp"

class VegetableGardenGenerator : public SectorFeature
{
  public:
    VegetableGardenGenerator();

  protected:
    void populate_vegetable_map();
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    std::map<int, std::string> vegetable_map;
    int vegetable_min;
    int vegetable_max;
};
