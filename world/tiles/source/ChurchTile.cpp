#include "ChurchTile.hpp"

// Needed by boost's serialization library:
ChurchTile::ChurchTile()
{
  tile_subtype = TILE_TYPE_UNDEFINED;
}

ChurchTile::ChurchTile(const TileType subtype)
{
  tile_subtype = subtype;
}

TileType ChurchTile::get_tile_type() const
{
  return TILE_TYPE_CHURCH;
}

std::string ChurchTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CHURCH;
}
