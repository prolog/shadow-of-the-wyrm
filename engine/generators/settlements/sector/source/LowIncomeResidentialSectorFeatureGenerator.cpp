#include "LowIncomeResidentialSectorFeatureGenerator.hpp"
#include "GardenGeneratorFactory.hpp"
#include "GraveyardGeneratorFactory.hpp"
#include "HouseSectorFeature.hpp"
#include "RNG.hpp"
#include "SectorFeature.hpp"
#include "ShopSectorFeature.hpp"

using namespace std;

LowIncomeResidentialSectorFeatureGenerator::LowIncomeResidentialSectorFeatureGenerator()
: features({{55, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_HOUSE},
            {65, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_GRAVES},
            {80, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_VEGETABLE_GARDEN},
            {90, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_SHOP},
            {100, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_SHOP}})
{
}

bool LowIncomeResidentialSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type)
{
  bool created = false;
  LowIncomeResidentialSectorFeatureType feat = static_cast<LowIncomeResidentialSectorFeatureType>(f_type);
  
  if (f_type == -1)
  {
    feat = get_random_feature(feat_idx);
  }

  SectorFeaturePtr feature;

  switch (feat)
  {
    case LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_HOUSE:
    {
      bool ruined = false;

      if (RNG::percent_chance(30))
      {
        ruined = true;
      }

      feature = make_shared<HouseSectorFeature>(ruined);
      break;
    }
    case LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_GRAVES:
    {
      feature = GraveyardGeneratorFactory::create_graveyard_sector_generator();
      break;
    }
    case LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_VEGETABLE_GARDEN:
    {
      feature = GardenGeneratorFactory::create_garden_generator(GardenType::GARDEN_TYPE_VEGETABLE);
      break;
    }
    case LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_ROCK_GARDEN:
    {
      feature = GardenGeneratorFactory::create_garden_generator(GardenType::GARDEN_TYPE_ROCK);
      break;
    }
    case LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_SHOP:
    default:
    {
      feature = make_shared<ShopSectorFeature>();
      break;
    }
  }

  if (feature != nullptr)
  {
    created = feature->generate(map, start_coord, end_coord);
  }

  return created;
}

LowIncomeResidentialSectorFeatureType LowIncomeResidentialSectorFeatureGenerator::get_random_feature(const int feat_idx) const
{
  for (const auto f_pair : features)
  {
    if (feat_idx < f_pair.first)
    {
      return f_pair.second;
    }
  }

  return LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_HOUSE;
}

