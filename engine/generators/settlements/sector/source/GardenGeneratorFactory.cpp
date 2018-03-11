#include "GardenGeneratorFactory.hpp"
#include "RNG.hpp"
#include "RockGardenGenerator.hpp"
#include "ShadeGardenGenerator.hpp"
#include "VegetableGardenGenerator.hpp"
#include "WildflowerGardenGenerator.hpp"

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
    case GardenType::GARDEN_TYPE_SHADE:
      garden_gen = std::make_shared<ShadeGardenGenerator>(map, start_row, start_col, height, width);
      break;
      case GardenType::GARDEN_TYPE_ROCK:
      garden_gen = std::make_shared<RockGardenGenerator>(map, start_row, start_col, height, width);
      break;
    case GardenType::GARDEN_TYPE_WILDFLOWER:
      garden_gen = std::make_shared<WildflowerGardenGenerator>(map, start_row, start_col, height, width);
      break;
    case GardenType::GARDEN_TYPE_VEGETABLE:
    case GardenType::GARDEN_TYPE_LAST:
    default:
      garden_gen = std::make_shared<VegetableGardenGenerator>(map, start_row, start_col, height, width);
      break;
  }

  return garden_gen;
}

// Create a random GardenGenerator
GardenGeneratorPtr GardenGeneratorFactory::create_uniform_random_garden_generator(MapPtr map, const int start_row, const int start_col, const int height, const int width)
{
  GardenType garden_type = static_cast<GardenType>(RNG::range(static_cast<int>(GardenType::GARDEN_TYPE_FIRST), static_cast<int>(GardenType::GARDEN_TYPE_LAST)));
  return create_garden_generator(garden_type, map, start_row, start_col, height, width);
}
