#pragma once
#include "Map.hpp"

class CastleGeneratorStrategy
{
  public:
    virtual void generate(MapPtr generate_map) = 0;
    virtual ~CastleGeneratorStrategy() = default;
};

using CastleGeneratorStrategyPtr = std::unique_ptr<CastleGeneratorStrategy>;

