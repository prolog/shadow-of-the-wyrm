#pragma once
#include "Generator.hpp"

class ChurchGeneratorFactory
{
  public:
    // Right now, this does nothing...
    static GeneratorPtr create_generator();

  protected:
    ChurchGeneratorFactory();
};
