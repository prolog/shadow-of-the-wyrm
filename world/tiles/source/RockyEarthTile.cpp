#include "RockyEarthTile.hpp"

TileType RockyEarthTile::get_tile_type() const
{
  return TileType::TILE_TYPE_ROCKY_EARTH;
}

std::string RockyEarthTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ROCKY_EARTH;
}

Tile* RockyEarthTile::clone()
{
  return new RockyEarthTile(*this);
}

ClassIdentifier RockyEarthTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ROCKY_EARTH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/RockyEarthTile_test.cpp"
#endif
