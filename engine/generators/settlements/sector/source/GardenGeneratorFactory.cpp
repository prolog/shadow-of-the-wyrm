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
SectorFeaturePtr GardenGeneratorFactory::create_garden_generator(const GardenType type)
{
  SectorFeaturePtr garden_gen;
  
  switch(type)
  {
    case GardenType::GARDEN_TYPE_SHADE:
      garden_gen = std::make_shared<ShadeGardenGenerator>();
      break;
      case GardenType::GARDEN_TYPE_ROCK:
      garden_gen = std::make_shared<RockGardenGenerator>();
      break;
    case GardenType::GARDEN_TYPE_WILDFLOWER:
      garden_gen = std::make_shared<WildflowerGardenGenerator>();
      break;
    case GardenType::GARDEN_TYPE_VEGETABLE:
    case GardenType::GARDEN_TYPE_LAST:
    default:
      garden_gen = std::make_shared<VegetableGardenGenerator>();
      break;
  }

  return garden_gen;
}

// Create a random GardenGenerator
SectorFeaturePtr GardenGeneratorFactory::create_uniform_random_garden_generator()
{
  GardenType garden_type = static_cast<GardenType>(RNG::range(static_cast<int>(GardenType::GARDEN_TYPE_FIRST), static_cast<int>(GardenType::GARDEN_TYPE_LAST)));
  return create_garden_generator(garden_type);
}
