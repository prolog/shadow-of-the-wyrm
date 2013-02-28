#include <boost/foreach.hpp>
#include "CreatureGenerationValues.hpp"
#include "Serialize.hpp"

using namespace std;

CreatureGenerationValues::CreatureGenerationValues()
: GenerationValues(),
friendly(false),
base_experience_value(0)
{
}

CreatureGenerationValues::~CreatureGenerationValues()
{
}

bool CreatureGenerationValues::operator==(const CreatureGenerationValues& cgv)
{
  bool result = true;

  result = result && GenerationValues::operator==(cgv);

  result = result && (allowable_terrain_types == cgv.allowable_terrain_types);
  result = result && (friendly == cgv.friendly);
  result = result && (initial_hit_points == cgv.initial_hit_points);
  result = result && (base_experience_value == cgv.base_experience_value);

  return result;
}

void CreatureGenerationValues::add_allowable_terrain_type(const TileType additional_terrain_type)
{
  allowable_terrain_types.insert(additional_terrain_type);
}

void CreatureGenerationValues::clear_allowable_terrain_types()
{
  allowable_terrain_types.clear();
}

void CreatureGenerationValues::set_allowable_terrain_types(const set<TileType>& new_allowable_terrain_types)
{
  allowable_terrain_types = new_allowable_terrain_types;
}

set<TileType> CreatureGenerationValues::get_allowable_terrain_types() const
{
  return allowable_terrain_types;
}

bool CreatureGenerationValues::is_terrain_type_allowed(const TileType terrain_type) const
{
  return (allowable_terrain_types.find(terrain_type) != allowable_terrain_types.end());
}

void CreatureGenerationValues::set_friendly(const bool new_friendly)
{
  friendly = new_friendly;
}

bool CreatureGenerationValues::get_friendly() const
{
  return friendly;
}

void CreatureGenerationValues::set_initial_hit_points(const Dice& new_initial_hit_points)
{
  initial_hit_points = new_initial_hit_points;
}

Dice CreatureGenerationValues::get_initial_hit_points() const
{
  return initial_hit_points;
}

void CreatureGenerationValues::set_base_experience_value(const uint new_base_experience)
{
  base_experience_value = new_base_experience;
}

uint CreatureGenerationValues::get_base_experience_value() const
{
  return base_experience_value;
}

bool CreatureGenerationValues::serialize(ostream& stream)
{
  GenerationValues::serialize(stream);

  size_t terrain_types_size = allowable_terrain_types.size();
  Serialize::write_size_t(stream, terrain_types_size);

  if (terrain_types_size > 0)
  {
    BOOST_FOREACH(TileType allowable_type, allowable_terrain_types)
    {
      Serialize::write_enum(stream, allowable_type);
    }
  }

  Serialize::write_bool(stream, friendly);
  initial_hit_points.serialize(stream);
  Serialize::write_uint(stream, base_experience_value);

  return true;
}

bool CreatureGenerationValues::deserialize(istream& stream)
{
  GenerationValues::deserialize(stream);

  size_t terrain_types_size = 0;
  Serialize::read_size_t(stream, terrain_types_size);

  if (terrain_types_size > 0)
  {
    allowable_terrain_types.clear();

    for (unsigned int i = 0; i < terrain_types_size; i++)
    {
      TileType allowable_type = TILE_TYPE_UNDEFINED;
      Serialize::read_enum(stream, allowable_type);

      allowable_terrain_types.insert(allowable_type);
    }
  }

  Serialize::read_bool(stream, friendly);
  initial_hit_points.deserialize(stream);
  Serialize::read_uint(stream, base_experience_value);

  return true;
}

ClassIdentifier CreatureGenerationValues::internal_class_identifier() const
{
  return CLASS_ID_CREATURE_GENERATION_VALUES;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureGenerationValues_test.cpp"
#endif