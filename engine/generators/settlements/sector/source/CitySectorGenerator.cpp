#include "CitySectorGenerator.hpp"
#include "SectorFeatureGeneratorFactory.hpp"

using namespace std;

bool CitySectorGenerator::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const CitySectorType sector_type)
{
  bool feature_generated = false;

  if (map != nullptr)
  {
    SectorFeatureGeneratorPtr sfg = SectorFeatureGeneratorFactory::create(sector_type);

    if (sfg != nullptr)
    {
      feature_generated = sfg->generate_feature(map, start_coord, end_coord);
    }
  }

  return feature_generated;
}
