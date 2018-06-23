#include "LowIncomeResidentialSectorFeatureGenerator.hpp"
#include "GraveyardGeneratorFactory.hpp"
#include "HouseSectorFeature.hpp"
#include "RNG.hpp"
#include "SectorFeature.hpp"

using namespace std;


LowIncomeResidentialSectorFeatureGenerator::LowIncomeResidentialSectorFeatureGenerator()
: features({{80, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_HOUSE},
            {100, LowIncomeResidentialSectorFeatureType::LIR_SECTOR_FEATURE_GRAVES}})
{
}

bool LowIncomeResidentialSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx)
{
  bool created = false;
  LowIncomeResidentialSectorFeatureType feat = get_random_feature(feat_idx);
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
    default:
    {
      feature = GraveyardGeneratorFactory::create_graveyard_sector_generator();
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

