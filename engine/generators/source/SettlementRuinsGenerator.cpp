#include "SettlementRuinsGenerator.hpp"

SettlementRuinsGenerator::SettlementRuinsGenerator(MapPtr new_base_map)
: SettlementGenerator(new_base_map, 90)
{
  // 90% chance of a given generated tile being generated; otherwise, the original tile will be used.
  // This simulates ruin.
}

MapPtr SettlementRuinsGenerator::generate()
{
  MapPtr result_map = SettlementGenerator::generate();

  return result_map;
}
