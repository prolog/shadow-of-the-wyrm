#include "FieldGenerator.hpp"
#include "RuinsGenerator.hpp"
#include "SettlementRuinsGenerator.hpp"
#include "KeepRuinsGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

RuinsGenerator::RuinsGenerator(const string& map_exit_id, const TileType tile_type, const RuinsType new_rt)
: Generator(map_exit_id, tile_type), rt(new_rt)
{
}

MapPtr RuinsGenerator::generate(MapPtr map, const RuinsType& ruins_type)
{
  MapPtr result_map;

  if (ruins_type == RuinsType::RUINS_TYPE_SETTLEMENT)
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

MapPtr RuinsGenerator::generate(const Dimensions& dim)
{
  TilePtr null_tile;

  // JCD FIXME: At some point, may want to make the base map type configurable...
  FieldGenerator fg(map_exit_id);
  MapPtr base_map = fg.generate(dim);

  return generate(base_map, rt);
}

bool RuinsGenerator::get_permanence_default() const
{
  return true;
}

// Generate a number of ruined buildings by doing a random walk starting at the
// top left corner of the map.
MapPtr RuinsGenerator::generate_ruined_settlement(MapPtr map)
{
  MapPtr result_map = std::make_shared<Map>(*map);

  return result_map;
}

