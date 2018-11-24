#pragma once
#include "CitySectorTypes.hpp"
#include "SectorFeatureGenerator.hpp"

class SectorFeatureGeneratorFactory
{
  public:
    static SectorFeatureGeneratorPtr create(const CitySectorType sector_type);
};

