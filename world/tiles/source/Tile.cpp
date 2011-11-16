#include "Tile.hpp"

/*
 ******************************************************************

  Routines for creating and setting/getting attributes of a given
  Tile.

 ******************************************************************/
Tile::Tile()
{
  set_default_properties();
  tile_type = TILE_TYPE_UNDEFINED;
}

void Tile::set_default_properties()
{
  illuminated = true;
  explored    = false;
}

void Tile::set_illuminated(bool new_illuminated)
{
  illuminated = new_illuminated;
}

bool Tile::get_illuminated() const
{
  return illuminated;
}

void Tile::set_explored(bool new_explored)
{
  explored = new_explored;
}

bool Tile::get_explored() const
{
  return explored;
}


TileType Tile::get_tile_type() const
{
  return tile_type;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tile_test.cpp"
#endif
