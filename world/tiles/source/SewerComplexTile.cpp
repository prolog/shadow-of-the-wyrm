#include "SewerComplexTile.hpp"

TileType SewerComplexTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SEWER_COMPLEX;
}

std::string SewerComplexTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SEWER_COMPLEX;
}

Tile* SewerComplexTile::clone()
{
  return new SewerComplexTile(*this);
}

ClassIdentifier SewerComplexTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SEWER_COMPLEX_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SewerComplexTile_test.cpp"
#endif
