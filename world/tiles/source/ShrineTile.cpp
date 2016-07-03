#include "ShrineTile.hpp"

TileType ShrineTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SHRINE;
}

std::string ShrineTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SHRINE;
}

Tile* ShrineTile::clone()
{
  return new ShrineTile(*this);
}

ClassIdentifier ShrineTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SHRINE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShrineTile_test.cpp"
#endif
