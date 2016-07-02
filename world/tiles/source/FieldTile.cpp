#include "FieldTile.hpp"
#include "ItemTypes.hpp"

const int FIELD_TILE_UNDEAD_PCT = 1;
const int FIELD_TILE_ITEM_PCT = 2;

FieldTile::FieldTile()
: WorldMapTile({ FIELD_TILE_UNDEAD_PCT, FIELD_TILE_ITEM_PCT, {ItemIdKeys::ITEM_ID_ROOT} })
{
}

TileType FieldTile::get_tile_type() const
{
  return TileType::TILE_TYPE_FIELD;
}

std::string FieldTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_FIELD;
}

Tile* FieldTile::clone()
{
  return new FieldTile(*this);
}

ClassIdentifier FieldTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FIELD_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/FieldTile_test.cpp"
#endif
