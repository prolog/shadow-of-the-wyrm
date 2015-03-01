#include "EarthTile.hpp"

TileType EarthTile::get_tile_type() const
{
  return TileType::TILE_TYPE_EARTH;
}

std::string EarthTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_EARTH;
}

int EarthTile::get_movement_multiplier() const
{
  return 0;
}

Tile* EarthTile::clone()
{
  return new EarthTile(*this);
}
ClassIdentifier EarthTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EARTH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/EarthTile_test.cpp"
#endif
