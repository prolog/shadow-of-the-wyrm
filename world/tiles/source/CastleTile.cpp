#include "CastleTile.hpp"

TileType CastleTile::get_tile_type() const
{
  return TileType::TILE_TYPE_CASTLE;
}

std::string CastleTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CASTLE;
}

bool CastleTile::is_interior() const
{
  return true;
}

Tile* CastleTile::clone()
{
  return new CastleTile(*this);
}

ClassIdentifier CastleTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CASTLE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/CastleTile_test.cpp"
#endif
