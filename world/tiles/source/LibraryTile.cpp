#include "LibraryTile.hpp"

TileType LibraryTile::get_tile_type() const
{
  return TILE_TYPE_LIBRARY;
}

std::string LibraryTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_LIBRARY;
}

Tile* LibraryTile::clone()
{
  return new LibraryTile(*this);
}

ClassIdentifier LibraryTile::internal_class_identifier() const
{
  return CLASS_ID_LIBRARY_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/LibraryTile_test.cpp"
#endif