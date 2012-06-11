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
  tile_subtype = TILE_TYPE_UNDEFINED;
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
  viewed      = false;
}

void Tile::set_illuminated(bool new_illuminated)
{
  illuminated = new_illuminated;
}

bool Tile::get_illuminated() const
{
  return illuminated;
}

bool Tile::get_is_blocking() const
{
  return (get_movement_multiplier() == 0);
}

int Tile::get_movement_multiplier() const
{
  return 1;
}

void Tile::set_explored(bool new_explored)
{
  explored = new_explored;
}

bool Tile::get_explored() const
{
  return explored;
}

void Tile::set_viewed(bool new_viewed)
{
  viewed = new_viewed;
}

bool Tile::get_viewed() const
{
  return viewed;
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
  
  if (creature->get_is_player())
  {
    set_explored(true);
  }
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

void Tile::set_tile_subtype(const TileType new_tile_subtype)
{
  tile_subtype = new_tile_subtype;
}

TileType Tile::get_tile_subtype() const
{
  return tile_subtype;
}

TileExitMap& Tile::get_tile_exit_map_ref()
{
  return map_exits;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tile_test.cpp"
#endif
