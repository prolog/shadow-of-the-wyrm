#pragma once
#include "GardenTypes.hpp"
#include "Map.hpp"
#include "SectorFeature.hpp"

class GardenGeneratorFactory
{
  public:
    static SectorFeaturePtr create_garden_generator(const GardenType garden_type);
    static SectorFeaturePtr create_uniform_random_garden_generator();

  protected:
    GardenGeneratorFactory();
    ~GardenGeneratorFactory();
};
