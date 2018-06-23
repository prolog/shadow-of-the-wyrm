#pragma once
#include "Generator.hpp"
#include "SectorFeature.hpp"

class GraveyardGeneratorFactory
{
  public:
    static GeneratorPtr create_ordered_graveyard_generator(const std::string& map_exit_id, const bool include_tomb);
    static GeneratorPtr create_scattered_graveyard_generator(const std::string& map_exit_id, const bool include_tomb);
    static SectorFeaturePtr create_graveyard_sector_generator();

  protected:
    GraveyardGeneratorFactory();
    ~GraveyardGeneratorFactory();
};
