#include "PublicAreaSectorFeatureGenerator.hpp"
#include "ParkSectorFeature.hpp"
#include "PlazaSectorFeature.hpp"
#include "ShopSectorFeature.hpp"
#include "TombSectorFeature.hpp"

using namespace std;


PublicAreaSectorFeatureGenerator::PublicAreaSectorFeatureGenerator()
: features({{103, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PLAZA},
            {102, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_SHOP},
            {100, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK},
            {103, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_TOMB}})
{
}

bool PublicAreaSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx)
{
  bool created = false;
  PublicSectorFeatureType feat = get_random_feature(feat_idx);
  SectorFeaturePtr feature;

  switch (feat)
  {
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PLAZA:
      feature = make_shared<PlazaSectorFeature>();
      break;
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_SHOP:
      feature = make_shared<ShopSectorFeature>();
      break;
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_TOMB:
      feature = make_shared<TombSectorFeature>();
      break;
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK:
    default:
      feature = make_shared<ParkSectorFeature>();
      break;
  }

  if (feature != nullptr)
  {
    created = feature->generate(map, start_coord, end_coord);
  }

  return created;
}

PublicSectorFeatureType PublicAreaSectorFeatureGenerator::get_random_feature(const int feat_idx) const
{
  for (const auto f_pair : features)
  {
    if (feat_idx < f_pair.first)
    {
      return f_pair.second;
    }
  }

  return PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK;
}

