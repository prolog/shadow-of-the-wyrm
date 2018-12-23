#include "ResidentialSectorFeatureGenerator.hpp"
#include "GardenGeneratorFactory.hpp"
#include "GraveyardGeneratorFactory.hpp"
#include "HouseSectorFeature.hpp"
#include "ShopSectorFeature.hpp"
#include "ShrineSectorFeature.hpp"
#include "WorkshopSectorFeature.hpp"

using namespace std;

ResidentialSectorFeatureGenerator::ResidentialSectorFeatureGenerator()
: features({{10, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_GRAVES},
            {15, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_FLOWER_GARDEN},
            {20, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_ROCK_GARDEN},
            {23, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_GARDEN},
            {35, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_SHOP},
            {45, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_SHRINE},
            {50, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_WORKSHOP},
            {100, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_HOUSE}})
{
}

bool ResidentialSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type)
{
  bool created = false;
  ResidentialSectorFeatureType feat = static_cast<ResidentialSectorFeatureType>(f_type);
  
  if (f_type == -1)
  {
    feat = get_random_feature(feat_idx);
  }

  SectorFeaturePtr feature;

  switch (feat)
  {
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_GRAVES:
    {
      feature = GraveyardGeneratorFactory::create_graveyard_sector_generator();
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_ROCK_GARDEN:
    {
      feature = GardenGeneratorFactory::create_garden_generator(GardenType::GARDEN_TYPE_ROCK);
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_FLOWER_GARDEN:
    {
      feature = GardenGeneratorFactory::create_garden_generator(GardenType::GARDEN_TYPE_WILDFLOWER);
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_GARDEN:
    {
      feature = GardenGeneratorFactory::create_uniform_random_garden_generator();
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_SHOP:
    {
      feature = make_shared<ShopSectorFeature>();
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_SHRINE:
    {
      feature = make_shared<ShrineSectorFeature>();
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_WORKSHOP:
    {
      feature = make_shared<WorkshopSectorFeature>();
      break;
    }
    case ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_HOUSE:
    default:
    {
      feature = make_shared<HouseSectorFeature>(false);
      break;
    }
  }

  if (feature != nullptr)
  {
    created = feature->generate(map, start_coord, end_coord);
  }

  return created;
}

ResidentialSectorFeatureType ResidentialSectorFeatureGenerator::get_random_feature(const int feat_idx) const
{
  for (const auto f_pair : features)
  {
    if (feat_idx < f_pair.first)
    {
      return f_pair.second;
    }
  }

  return ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_GARDEN;
}

