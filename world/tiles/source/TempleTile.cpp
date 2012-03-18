#include "TempleTile.hpp"

TileType TempleTile::get_tile_type() const
{
  return TILE_TYPE_TEMPLE;
}

std::string TempleTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_TEMPLE;
}
