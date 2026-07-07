#include "IcebergTile.hpp"

TileType IcebergTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SEA;
}

std::string IcebergTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ICEBERG;
}

Tile* IcebergTile::clone()
{
  return new IcebergTile(*this);
}

ClassIdentifier IcebergTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ICEBERG_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/IcebergTile_test.cpp"
#endif
