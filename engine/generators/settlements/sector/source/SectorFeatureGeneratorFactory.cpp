#include "SectorFeatureGeneratorFactory.hpp"
#include "DefaultSectorFeatureGenerator.hpp"
#include "LowIncomeResidentialSectorFeatureGenerator.hpp"
#include "PublicAreaSectorFeatureGenerator.hpp"
#include "ReligiousCommercialSectorFeatureGenerator.hpp"
#include "ResidentialSectorFeatureGenerator.hpp"

SectorFeatureGeneratorPtr SectorFeatureGeneratorFactory::create(const CitySectorType sector_type)
{
  SectorFeatureGeneratorPtr sfg;

  switch(sector_type)
  {
    case CitySectorType::CITY_SECTOR_PUBLIC_AREA:
      sfg = std::make_unique<PublicAreaSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_LOW_INCOME_RESIDENTIAL:
      sfg = std::make_unique<LowIncomeResidentialSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_RELIGIOUS_COMMERCIAL:
      sfg = std::make_unique<ReligiousCommercialSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_RESIDENTIAL:
      sfg = std::make_unique<ResidentialSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_NULL:
    default:
      sfg = std::make_unique<DefaultSectorFeatureGenerator>();
      break;
  }

  return sfg;
}
