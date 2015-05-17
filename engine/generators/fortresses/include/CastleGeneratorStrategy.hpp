#pragma once
#include "Map.hpp"

class CastleGeneratorStrategy
{
  public:
    virtual void generate(MapPtr generate_map) = 0;
};

typedef std::shared_ptr<CastleGeneratorStrategy> CastleGeneratorStrategyPtr;

