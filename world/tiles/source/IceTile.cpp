#include "IceTile.hpp"
#include "ItemTypes.hpp"

// You can always get ice by digging ice tiles.
IceTile::IceTile()
: Tile({ 0, 100, {ItemIdKeys::ITEM_ID_GLACIAL_ICE}})
{
}

TileType IceTile::get_tile_type() const
{
  return TileType::TILE_TYPE_ICE;
}

std::string IceTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ICE;
}

bool IceTile::has_detritus() const
{
  return false;
}

Tile* IceTile::clone()
{
  return new IceTile(*this);
}

ClassIdentifier IceTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ICE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/IceTile_test.cpp"
#endif
