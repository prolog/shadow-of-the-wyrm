#pragma once
#include "CastleGeneratorStrategy.hpp"

class MotteBaileyCastleGeneratorStrategy : public CastleGeneratorStrategy
{
  public:
    void generate(MapPtr castle_map);
};

