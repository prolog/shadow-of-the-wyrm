#include "KeepTile.hpp"

TileType KeepTile::get_tile_type() const
{
  return TILE_TYPE_KEEP;
}

std::string KeepTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_KEEP;
}
