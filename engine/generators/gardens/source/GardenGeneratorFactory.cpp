#include <boost/make_shared.hpp>
#include "GardenGeneratorFactory.hpp"
#include "RNG.hpp"
#include "RockGardenGenerator.hpp"
#include "ShadeGardenGenerator.hpp"
#include "VegetableGardenGenerator.hpp"
#include "WildflowerGardenGenerator.hpp"

using boost::make_shared;

GardenGeneratorFactory::GardenGeneratorFactory()
{
}

GardenGeneratorFactory::~GardenGeneratorFactory()
{
}

// Create a GardenGenerator
GardenGeneratorPtr GardenGeneratorFactory::create_garden_generator(const GardenType type, MapPtr map, const int start_row, const int start_col, const int height, const int width)
{
  GardenGeneratorPtr garden_gen;
  
  switch(type)
  {
    case GARDEN_TYPE_SHADE:
      garden_gen = make_shared<ShadeGardenGenerator>(map, start_row, start_col, height, width);
      break;
    case GARDEN_TYPE_ROCK:
      garden_gen = make_shared<RockGardenGenerator>(map, start_row, start_col, height, width);
      break;
    case GARDEN_TYPE_WILDFLOWER:
      garden_gen = make_shared<WildflowerGardenGenerator>(map, start_row, start_col, height, width);
      break;
    case GARDEN_TYPE_VEGETABLE:
    case GARDEN_TYPE_LAST:
    default:
      garden_gen = make_shared<VegetableGardenGenerator>(map, start_row, start_col, height, width);
      break;
  }

  return garden_gen;
}

// Create a random GardenGenerator
GardenGeneratorPtr GardenGeneratorFactory::create_uniform_random_garden_generator(MapPtr map, const int start_row, const int start_col, const int height, const int width)
{
  GardenType garden_type = static_cast<GardenType>(RNG::range(GARDEN_TYPE_FIRST, GARDEN_TYPE_LAST));
  return create_garden_generator(garden_type, map, start_row, start_col, height, width);
}
