#include "RockTile.hpp"

TileType RockTile::get_tile_type() const
{
  return TILE_TYPE_ROCK;
}

std::string RockTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ROCK;
}

// JCD FIXME: This can probably be deleted later on, since Tile's version
// should cover it (but ensure that the movement multiplier is 0 for RockTile).
bool RockTile::get_is_blocking(CreaturePtr perspective_creature) const
{
  return true;
}

int RockTile::get_movement_multiplier() const
{
  return 0;
}

Tile* RockTile::clone()
{
  return new RockTile(*this);
}
ClassIdentifier RockTile::internal_class_identifier() const
{
  return CLASS_ID_ROCK_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/RockTile_test.cpp"
#endif
