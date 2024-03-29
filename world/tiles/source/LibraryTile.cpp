#include "LibraryTile.hpp"

TileType LibraryTile::get_tile_type() const
{
  return TileType::TILE_TYPE_LIBRARY;
}

std::string LibraryTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_LIBRARY;
}

bool LibraryTile::is_interior() const
{
  return true;
}

Tile* LibraryTile::clone()
{
  return new LibraryTile(*this);
}

ClassIdentifier LibraryTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_LIBRARY_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/LibraryTile_test.cpp"
#endif