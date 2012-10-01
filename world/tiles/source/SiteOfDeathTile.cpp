#include "SiteOfDeathTile.hpp"

// Needed by boost's serialization library:
SiteOfDeathTile::SiteOfDeathTile()
{
  tile_subtype = TILE_TYPE_UNDEFINED;
}

SiteOfDeathTile::SiteOfDeathTile(const TileType subtype)
{
  tile_subtype = subtype;
}

TileType SiteOfDeathTile::get_tile_type() const
{
  return TILE_TYPE_SITE_OF_DEATH;
}

std::string SiteOfDeathTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SITE_OF_DEATH;
}
