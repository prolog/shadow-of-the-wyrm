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

Tile::~Tile()
{
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

bool Tile::has_creature() const
{
  return (creature != NULL);
}

void Tile::set_creature(const CreaturePtr& new_creature)
{
  creature = new_creature;
}

void Tile::remove_creature()
{
  creature.reset();
}

CreaturePtr Tile::get_creature() const
{
  return creature;
}


TileType Tile::get_tile_type() const
{
  return tile_type;
}

TileExitMap& Tile::get_tile_exit_map_ref()
{
  return map_exits;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tile_test.cpp"
#endif
