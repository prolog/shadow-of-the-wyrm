#include "SiteOfDeathTile.hpp"

// Needed by boost's serialization library:
SiteOfDeathTile::SiteOfDeathTile()
{
  tile_subtype = TileType::TILE_TYPE_UNDEFINED;
}

SiteOfDeathTile::SiteOfDeathTile(const TileType subtype)
{
  tile_subtype = subtype;
}

TileType SiteOfDeathTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SITE_OF_DEATH;
}

std::string SiteOfDeathTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SITE_OF_DEATH;
}

bool SiteOfDeathTile::is_interior() const
{
  return true;
}

Tile* SiteOfDeathTile::clone()
{
  return new SiteOfDeathTile(*this);
}

ClassIdentifier SiteOfDeathTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SITE_OF_DEATH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SiteOfDeathTile_test.cpp"
#endif