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
      sfg = std::make_shared<PublicAreaSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_LOW_INCOME_RESIDENTIAL:
      sfg = std::make_shared<LowIncomeResidentialSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_RELIGIOUS_COMMERCIAL:
      sfg = std::make_shared<ReligiousCommercialSectorFeatureGenerator>();
      break;
    // JCD FIXME: Move above rel/comm once populated
    case CitySectorType::CITY_SECTOR_RESIDENTIAL:
      sfg = std::make_shared<ResidentialSectorFeatureGenerator>();
      break;
    case CitySectorType::CITY_SECTOR_NULL:
    default:
      sfg = std::make_shared<DefaultSectorFeatureGenerator>();
      break;
  }

  return sfg;
}
