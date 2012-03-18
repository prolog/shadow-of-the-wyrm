#include "ChurchTile.hpp"

TileType ChurchTile::get_tile_type() const
{
  return TILE_TYPE_CHURCH;
}

std::string ChurchTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CHURCH;
}
