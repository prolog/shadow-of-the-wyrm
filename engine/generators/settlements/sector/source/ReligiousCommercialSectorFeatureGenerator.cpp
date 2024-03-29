#include "ReligiousCommercialSectorFeatureGenerator.hpp"
#include "DeityUtils.hpp"
#include "GardenGeneratorFactory.hpp"
#include "LibrarySectorFeature.hpp"
#include "ShopSectorFeature.hpp"
#include "StorehouseSectorFeature.hpp"

using namespace std;

ReligiousCommercialSectorFeatureGenerator::ReligiousCommercialSectorFeatureGenerator()
: features({{10, ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_STOREHOUSE},
            {30, ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_SHOP},
            {50, ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_OUTDOOR_SHRINE},
            {70, ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_LIBRARY},
            {100, ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_GARDEN}})
{
}

bool ReligiousCommercialSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx, const int f_type)
{
  bool created = false;
  ReligiousCommercialSectorFeatureType feat = static_cast<ReligiousCommercialSectorFeatureType>(f_type);
  
  if (f_type == -1)
  {
    feat = get_random_feature(feat_idx);
  }

  SectorFeaturePtr feature;

  switch (feat)
  {
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_ROCK_GARDEN:
    {
      feature = GardenGeneratorFactory::create_garden_generator(GardenType::GARDEN_TYPE_ROCK);
      break;
    }
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_FLOWER_GARDEN:
    {
      feature = GardenGeneratorFactory::create_garden_generator(GardenType::GARDEN_TYPE_WILDFLOWER);
      break;
    }
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_SHOP:
    {
      feature = std::make_unique<ShopSectorFeature>();
      break;
    }
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_LIBRARY:
    {
      feature = std::make_unique<LibrarySectorFeature>();
      break;
    }
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_STOREHOUSE:
    {
      feature = std::make_unique<StorehouseSectorFeature>();
      break;
    }
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_OUTDOOR_SHRINE:
    {
      Game& game = Game::instance();
      auto deity_details = DeityUtils::get_random_deity_with_align(game);
      Deity* deity = deity_details.first;
      string deity_id;

      if (deity != nullptr)
      {
        deity_id = deity->get_id();
      }

      SectorFeaturePtr garden = GardenGeneratorFactory::create_uniform_random_garden_generator(deity_id, deity_details.second);
      feature = std::move(garden);

      break;
    }
    case ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_GARDEN:
    default:
    {
      feature = GardenGeneratorFactory::create_uniform_random_garden_generator();
      break;
    }
  }

  if (feature != nullptr)
  {
    created = feature->generate(map, start_coord, end_coord);
  }

  return created;
}

ReligiousCommercialSectorFeatureType ReligiousCommercialSectorFeatureGenerator::get_random_feature(const int feat_idx) const
{
  for (const auto f_pair : features)
  {
    if (feat_idx < f_pair.first)
    {
      return f_pair.second;
    }
  }

  return ReligiousCommercialSectorFeatureType::RC_SECTOR_FEATURE_GARDEN;
}

