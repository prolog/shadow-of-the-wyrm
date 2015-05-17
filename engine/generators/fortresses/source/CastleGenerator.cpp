#include "CastleGenerator.hpp"
#include "CastleGeneratorStrategyFactory.hpp"
#include "TerrainGeneratorFactory.hpp"

using namespace std;

CastleGenerator::CastleGenerator(const string& map_exit_id, const TileType base_tile, const CastleType new_castle_type)
: Generator(map_exit_id, TileType::TILE_TYPE_CASTLE), base_tile_type(base_tile), castle_type(new_castle_type)
{
}

MapPtr CastleGenerator::generate(const Dimensions& dim)
{
  GeneratorPtr gen = TerrainGeneratorFactory::create_generator(nullptr, map_exit_id, base_tile_type);
  MapPtr result_map = gen->generate(dim);

  generate_castle(result_map);

  return result_map;
}

void CastleGenerator::generate_castle(MapPtr castle_map)
{
  CastleGeneratorStrategyPtr castle_strategy = CastleGeneratorStrategyFactory::create_strategy(castle_type);
  castle_strategy->generate(castle_map);
}

bool CastleGenerator::get_permanence_default() const
{
  return true;
}

