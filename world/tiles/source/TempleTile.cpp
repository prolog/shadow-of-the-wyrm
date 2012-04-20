#include "TempleTile.hpp"

TempleTile::TempleTile(const TileType subtype)
{
  tile_subtype = subtype;
}

TileType TempleTile::get_tile_type() const
{
  return TILE_TYPE_TEMPLE;
}

std::string TempleTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_TEMPLE;
}
