#pragma once
#include "Generator.hpp"

class GraveyardGeneratorFactory
{
  public:
    static GeneratorPtr create_ordered_graveyard_generator(const std::string& map_exit_id, const bool include_tomb);
    static GeneratorPtr create_scattered_graveyard_generator(const std::string& map_exit_id, const bool include_tomb);

  protected:
    GraveyardGeneratorFactory();
    ~GraveyardGeneratorFactory();
};
