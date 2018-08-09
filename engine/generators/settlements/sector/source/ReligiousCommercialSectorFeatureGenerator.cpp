#include "ReligiousCommercialSectorFeatureGenerator.hpp"
#include "GardenGeneratorFactory.hpp"

using namespace std;

ReligiousCommercialSectorFeatureGenerator::ReligiousCommercialSectorFeatureGenerator()
: features({{100, ReligiousCommercialSectorFeatureType::LIR_SECTOR_FEATURE_GARDEN}})
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
    case ReligiousCommercialSectorFeatureType::LIR_SECTOR_FEATURE_GARDEN:
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

  return ReligiousCommercialSectorFeatureType::LIR_SECTOR_FEATURE_GARDEN;
}

