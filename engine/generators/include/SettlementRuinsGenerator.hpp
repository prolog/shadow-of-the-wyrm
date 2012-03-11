#pragma once
#include "Map.hpp"
#include "SettlementGenerator.hpp"

class SettlementRuinsGenerator : public SettlementGenerator
{
  public:
    SettlementRuinsGenerator(MapPtr new_base_map);
    virtual MapPtr generate();
};
