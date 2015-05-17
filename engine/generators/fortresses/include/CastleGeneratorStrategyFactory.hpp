#pragma once
#include "CastleGenerator.hpp"
#include "CastleGeneratorStrategy.hpp"

class CastleGeneratorStrategyFactory
{
  public:
    static CastleGeneratorStrategyPtr create_strategy(const CastleType castle_type);
};

