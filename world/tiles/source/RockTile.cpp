#include "RockTile.hpp"
#include "ItemTypes.hpp"

using namespace std;

const int RockTile::ROCK_TILE_HARDNESS = 10;

RockTile::RockTile()
: Tile(ROCK_TILE_HARDNESS)
{
}

TileType RockTile::get_tile_type() const
{
  return TileType::TILE_TYPE_ROCK;
}

TileType RockTile::get_decomposition_tile_type() const
{
  return TileType::TILE_TYPE_ROCKY_EARTH;
}

float RockTile::get_breakage_multiplier() const
{
  return 1.0f;
}

vector<pair<pair<int, int>, string>> RockTile::get_decomposition_item_ids() const
{
  vector<pair<pair<int, int>, string>> result = {{{1,100}, ItemIdKeys::ITEM_ID_MAGICI_SHARD},
                                                 {{1,120}, ItemIdKeys::ITEM_ID_LUMP_GOLD},
                                                 {{1,30}, ItemIdKeys::ITEM_ID_IRON_INGOT},
                                                 {{1,50}, ItemIdKeys::ITEM_ID_STEEL_INGOT},
                                                 {{1,10}, ItemIdKeys::ITEM_ID_COAL},
                                                 {{1,6}, ItemIdKeys::ITEM_ID_STONE},
                                                 {{1,6}, ItemIdKeys::ITEM_ID_ROCK}};
  return result;
}

string RockTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ROCK;
}

int RockTile::get_movement_multiplier() const
{
  return 0;
}

Tile* RockTile::clone()
{
  return new RockTile(*this);
}
ClassIdentifier RockTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ROCK_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/RockTile_test.cpp"
#endif
