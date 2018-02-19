#include "SectorFeatureGeneratorFactory.hpp"
#include "DefaultSectorFeatureGenerator.hpp"
#include "PublicAreaSectorFeatureGenerator.hpp"

SectorFeatureGeneratorPtr SectorFeatureGeneratorFactory::create(const CitySectorType sector_type)
{
  SectorFeatureGeneratorPtr sfg;

  switch(sector_type)
  {
    case CitySectorType::CITY_SECTOR_PUBLIC_AREA:
      sfg = std::make_shared<PublicAreaSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_LOW_INCOME_RESIDENTIAL:
    case CitySectorType::CITY_SECTOR_RESIDENTIAL:
    case CitySectorType::CITY_SECTOR_RELIGIOUS_COMMERCIAL:
    case CitySectorType::CITY_SECTOR_NULL:
    default:
      sfg = std::make_shared<DefaultSectorFeatureGenerator>();
      break;
  }

  return sfg;
}
