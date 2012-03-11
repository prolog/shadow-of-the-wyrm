#include "Inventory.hpp"
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

bool Tile::display_description_on_arrival() const
{
  return false;
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

bool Tile::has_feature() const
{
  return (feature);
}

void Tile::set_feature(FeaturePtr new_feature)
{
  feature = new_feature;
}

FeaturePtr Tile::get_feature()
{
  return feature;
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

Inventory& Tile::get_items()
{
  return items;
}


TileType Tile::get_tile_type() const
{
  return tile_type;
}

TileType Tile::get_tile_subtype() const
{
  return TILE_TYPE_UNDEFINED;
}

TileExitMap& Tile::get_tile_exit_map_ref()
{
  return map_exits;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tile_test.cpp"
#endif
