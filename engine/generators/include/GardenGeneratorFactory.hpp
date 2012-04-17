#pragma once
#include "GardenGenerator.hpp"
#include "GardenTypes.hpp"

class GardenGeneratorFactory
{
  public:
    static GardenGeneratorPtr create_garden_generator(const GardenType garden_type, MapPtr map, const int start_row, const int start_col, const int height, const int width);
    static GardenGeneratorPtr create_uniform_random_garden_generator(MapPtr map, const int start_row, const int start_col, const int height, const int width);

  protected:
    GardenGeneratorFactory();
    ~GardenGeneratorFactory();
};
