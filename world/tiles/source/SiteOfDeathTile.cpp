#include "SiteOfDeathTile.hpp"

TileType SiteOfDeathTile::get_tile_type() const
{
  return TILE_TYPE_SITE_OF_DEATH;
}

std::string SiteOfDeathTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SITE_OF_DEATH;
}
