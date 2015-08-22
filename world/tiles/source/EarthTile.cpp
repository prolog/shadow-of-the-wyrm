#include "EarthTile.hpp"

using namespace std;

const int EarthTile::EARTH_TILE_HARDNESS = 1;

TileType EarthTile::get_tile_type() const
{
  return TileType::TILE_TYPE_EARTH;
}

TileType EarthTile::get_decomposition_tile_type() const
{
  return TileType::TILE_TYPE_DUNGEON;
}

string EarthTile::get_decomposition_item_id() const
{
  return "_dirt";
}

int EarthTile::get_hardness() const
{
  return EarthTile::EARTH_TILE_HARDNESS;
}

string EarthTile::get_tile_description_sid() const
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
