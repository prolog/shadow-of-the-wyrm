#include "GraveTile.hpp"

TileType GraveTile::get_tile_type() const
{
  return TILE_TYPE_GRAVE;
}

std::string GraveTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_GRAVE;
}

Tile* GraveTile::clone()
{
  return new GraveTile(*this);
}

ClassIdentifier GraveTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GRAVE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/GraveTile_test.cpp"
#endif
