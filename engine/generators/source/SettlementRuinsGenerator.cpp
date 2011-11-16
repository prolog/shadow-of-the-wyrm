#include "SettlementRuinsGenerator.hpp"

SettlementRuinsGenerator::SettlementRuinsGenerator()
: SettlementGenerator(90)
{
  // 90% chance of a given generated tile being generated; otherwise, the original tile will be used.
  // This simulates ruin.
}

MapPtr SettlementRuinsGenerator::generate(MapPtr map)
{
  MapPtr result_map = SettlementGenerator::generate(map);

  return result_map;
}
