#include "BushTile.hpp"
#include "ItemTypes.hpp"

const int BUSH_TILE_UNDEAD_PCT = 0;
const int BUSH_TILE_ITEM_PCT = 3;

BushTile::BushTile()
: Tile({BUSH_TILE_UNDEAD_PCT, BUSH_TILE_ITEM_PCT, {ItemIdKeys::ITEM_ID_ROOT}})
{
}

TileType BushTile::get_tile_type() const
{
  return TileType::TILE_TYPE_BUSH;
}

std::string BushTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BUSH;
}

std::string BushTile::get_dig_message_sid() const
{
  return TileTextKeys::TILE_DIG_BUSH;
}

TileType BushTile::get_decomposition_tile_type() const
{
  return TileType::TILE_TYPE_FIELD;
}

std::vector<std::pair<std::pair<int, int>, std::string>> BushTile::get_decomposition_item_ids() const
{
  return { {{1, 2}, ItemIdKeys::ITEM_ID_BRANCH} };
}

Tile* BushTile::clone()
{
  return new BushTile(*this);
}

ClassIdentifier BushTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BUSH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/BushTile_test.cpp"
#endif
