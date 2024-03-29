#include "CryptTile.hpp"

TileType CryptTile::get_tile_type() const
{
  return TileType::TILE_TYPE_CRYPT;
}

std::string CryptTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CRYPT;
}

bool CryptTile::is_interior() const
{
  return true;
}

Tile* CryptTile::clone()
{
  return new CryptTile(*this);
}

ClassIdentifier CryptTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CRYPT_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/CryptTile_test.cpp"
#endif
