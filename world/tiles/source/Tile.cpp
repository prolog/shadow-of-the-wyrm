#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Inventory.hpp"
#include "FeatureFactory.hpp"
#include "MapFactory.hpp"
#include "Serialize.hpp"
#include "Tile.hpp"

using namespace std;

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
  return (get_movement_multiplier() == 0) || (feature && feature->get_is_blocking());
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

bool Tile::has_blocking_feature() const
{
  return (feature && feature->get_is_blocking());
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

// All tiles are assumed to be ground tiles, unless the derived class declares otherwise.
TileSuperType Tile::get_tile_super_type() const
{
  return TILE_SUPER_TYPE_GROUND;
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

bool Tile::get_dangerous() const
{
  return false;
}

string Tile::get_danger_confirmation_sid() const
{
  string empty_sid;
  return empty_sid;
}

bool Tile::serialize(ostream& stream)
{
  Serialize::write_bool(stream, illuminated);
  Serialize::write_bool(stream, explored);
  Serialize::write_bool(stream, viewed);
  Serialize::write_enum(stream, tile_type);
  Serialize::write_enum(stream, tile_subtype);

  if (creature)
  {
    Serialize::write_class_id(stream, creature->get_class_identifier());
    creature->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  if (feature)
  {
    Serialize::write_class_id(stream, feature->get_class_identifier());
    feature->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  // items

  Serialize::write_size_t(stream, map_exits.size());

  BOOST_FOREACH(TileExitMap::value_type& tile_exit_map_pair, map_exits)
  {
    Direction d = tile_exit_map_pair.first;
    MapExitPtr map_exit = tile_exit_map_pair.second;

    Serialize::write_enum(stream, d);

    if (map_exit)
    {
      Serialize::write_class_id(stream, map_exit->get_class_identifier());
      map_exit->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, CLASS_ID_NULL);
    }
  }

  return true;
}

bool Tile::deserialize(istream& stream)
{
  Serialize::read_bool(stream, illuminated);
  Serialize::read_bool(stream, explored);
  Serialize::read_bool(stream, viewed);
  Serialize::read_enum(stream, tile_type);
  Serialize::read_enum(stream, tile_subtype);

  ClassIdentifier creature_clid;
  Serialize::read_class_id(stream, creature_clid);

  if (creature_clid != CLASS_ID_NULL)
  {
    creature = boost::make_shared<Creature>();
    creature->deserialize(stream);
  }

  ClassIdentifier feature_clid;
  Serialize::read_class_id(stream, feature_clid);

  if (feature_clid != CLASS_ID_NULL)
  {
    FeaturePtr feature = FeatureFactory::create_feature(feature_clid);
    if (!feature) return false;
    if (!feature->deserialize(stream)) return false;
  }

  // items

  size_t map_size;
  Serialize::read_size_t(stream, map_size);

  map_exits.clear();

  for (unsigned int i = 0; i < map_size; i++)
  {
    Direction d = DIRECTION_NORTH; // just a random default value - otherwise, compiler warnings.
    Serialize::read_enum(stream, d);

    ClassIdentifier map_exit_clid;
    Serialize::read_class_id(stream, map_exit_clid);
    MapExitPtr current_dir_map_exit = MapFactory::create_map_exit();
    if (map_exit_clid != CLASS_ID_NULL)
    {
      current_dir_map_exit->deserialize(stream);
    }

    map_exits.insert(make_pair(d, current_dir_map_exit));
  }

  return true;
}

ClassIdentifier Tile::internal_class_identifier() const
{
  return CLASS_ID_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tile_test.cpp"
#endif
