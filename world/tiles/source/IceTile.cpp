#include "IceTile.hpp"

TileType IceTile::get_tile_type() const
{
  return TileType::TILE_TYPE_ICE;
}

std::string IceTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ICE;
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
