#include "CastleTile.hpp"

TileType CastleTile::get_tile_type() const
{
  return TILE_TYPE_CASTLE;
}

std::string CastleTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CASTLE;
}
