#include "ResidentialSectorFeatureGenerator.hpp"
#include "GardenGeneratorFactory.hpp"

using namespace std;

ResidentialSectorFeatureGenerator::ResidentialSectorFeatureGenerator()
: features({{100, ResidentialSectorFeatureType::RESIDENTIAL_SECTOR_FEATURE_GARDEN}})
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

