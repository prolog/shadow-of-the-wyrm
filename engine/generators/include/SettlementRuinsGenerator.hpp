#pragma once
#include "Map.hpp"
#include "SettlementGenerator.hpp"

class SettlementRuinsGenerator : public SettlementGenerator
{
  public:
    SettlementRuinsGenerator();
    virtual MapPtr generate(MapPtr map);
};
