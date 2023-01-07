#include "FloatingTowerTile.hpp"

TileType FloatingTowerTile::get_tile_type() const
{
  return TileType::TILE_TYPE_FLOATING_TOWER;
}

std::string FloatingTowerTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_FLOATING_TOWER;
}

bool FloatingTowerTile::is_interior() const
{
  return true;
}

Tile* FloatingTowerTile::clone()
{
  return new FloatingTowerTile(*this);
}

ClassIdentifier FloatingTowerTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FLOATING_TOWER_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/FloatingTowerTile_test.cpp"
#endif
