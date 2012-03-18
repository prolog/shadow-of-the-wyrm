#include "LibraryTile.hpp"

TileType LibraryTile::get_tile_type() const
{
  return TILE_TYPE_LIBRARY;
}

std::string LibraryTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_LIBRARY;
}
