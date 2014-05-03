#pragma once
#include "IPillarGenerator.hpp"
#include "PillarTypes.hpp"

// Factory class that generates IPillarGeneratorPtrs based on the type
// provided.
class PillarGeneratorFactory
{
  public:
    static IPillarGeneratorPtr create_generator(const PillarType pt);
};

