#include "BarracksTile.hpp"

TileType BarracksTile::get_tile_type() const
{
  return TILE_TYPE_BARRACKS;
}

std::string BarracksTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BARRACKS;
}
