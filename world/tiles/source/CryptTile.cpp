#include "CryptTile.hpp"

TileType CryptTile::get_tile_type() const
{
  return TILE_TYPE_CRYPT;
}

std::string CryptTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CRYPT;
}

Tile* CryptTile::clone()
{
  return new CryptTile(*this);
}

ClassIdentifier CryptTile::internal_class_identifier() const
{
  return CLASS_ID_CRYPT_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/CryptTile_test.cpp"
#endif
