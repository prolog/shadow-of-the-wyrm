#include "RuinsGenerator.hpp"
#include "SettlementRuinsGenerator.hpp"
#include "KeepRuinsGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

MapPtr RuinsGenerator::generate(MapPtr map, const RuinsType& ruins_type)
{
  MapPtr result_map;

  if (ruins_type == RUINS_TYPE_SETTLEMENT)
  {
    SettlementRuinsGenerator srg(map);
    result_map = srg.generate();
  }
  else
  {
    KeepRuinsGenerator krg(map);
    result_map = krg.generate();
  }

  return result_map;
}

// Generate a number of ruined buildings by doing a random walk starting at the
// top left corner of the map.
MapPtr RuinsGenerator::generate_ruined_settlement(MapPtr map)
{
  MapPtr result_map = std::make_shared<Map>(*map);

  return result_map;
}

