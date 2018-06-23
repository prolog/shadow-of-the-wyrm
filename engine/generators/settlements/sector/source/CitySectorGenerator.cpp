#include "CitySectorGenerator.hpp"
#include "SectorFeatureGeneratorFactory.hpp"

using namespace std;

bool CitySectorGenerator::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const CitySectorType sector_type, const int sector_feature_type)
{
  bool feature_generated = false;

  if (map != nullptr)
  {
    SectorFeatureGeneratorPtr sfg = SectorFeatureGeneratorFactory::create(sector_type);

    if (sfg != nullptr)
    {
      feature_generated = sfg->generate_feature(map, start_coord, end_coord, sector_feature_type);
    }
  }

  return feature_generated;
}
