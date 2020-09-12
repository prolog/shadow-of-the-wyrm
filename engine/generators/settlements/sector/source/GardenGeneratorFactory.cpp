#include "GardenGeneratorFactory.hpp"
#include "RNG.hpp"
#include "RockGardenGenerator.hpp"
#include "ShadeGardenGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"
#include "WildflowerGardenGenerator.hpp"

using namespace std;

GardenGeneratorFactory::GardenGeneratorFactory()
{
}

GardenGeneratorFactory::~GardenGeneratorFactory()
{
}

// Create a GardenGenerator
SectorFeaturePtr GardenGeneratorFactory::create_garden_generator(const GardenType type, const string& deity_id, const AlignmentRange ar)
{
  SectorFeaturePtr garden_gen;
  
  switch(type)
  {
    case GardenType::GARDEN_TYPE_SHADE:
      garden_gen = std::make_unique<ShadeGardenGenerator>(deity_id, ar);
      break;
      case GardenType::GARDEN_TYPE_ROCK:
      garden_gen = std::make_unique<RockGardenGenerator>(deity_id, ar);
      break;
    case GardenType::GARDEN_TYPE_WILDFLOWER:
      garden_gen = std::make_unique<WildflowerGardenGenerator>(deity_id, ar);
      break;
    case GardenType::GARDEN_TYPE_VEGETABLE:
    case GardenType::GARDEN_TYPE_LAST:
    default:
      garden_gen = std::make_unique<FruitVegetableGardenGenerator>(FruitVegetableGardenType::FVG_TYPE_VEGETABLE, deity_id, ar);
      break;
  }

  return garden_gen;
}

// Create a random GardenGenerator
SectorFeaturePtr GardenGeneratorFactory::create_uniform_random_garden_generator(const string& deity_id, const AlignmentRange align)
{
  GardenType garden_type = static_cast<GardenType>(RNG::range(static_cast<int>(GardenType::GARDEN_TYPE_FIRST), static_cast<int>(GardenType::GARDEN_TYPE_LAST)));
  return create_garden_generator(garden_type, deity_id, align);
}

