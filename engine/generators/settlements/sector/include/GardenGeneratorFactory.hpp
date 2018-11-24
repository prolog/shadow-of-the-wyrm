#pragma once
#include "AlignmentEnums.hpp"
#include "GardenTypes.hpp"
#include "Map.hpp"
#include "SectorFeature.hpp"

class GardenGeneratorFactory
{
  public:
    static SectorFeaturePtr create_garden_generator(const GardenType garden_type, const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);
    static SectorFeaturePtr create_uniform_random_garden_generator(const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);

  protected:
    GardenGeneratorFactory();
    ~GardenGeneratorFactory();
};
