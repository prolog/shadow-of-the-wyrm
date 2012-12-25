#include "CreatureGenerationValues.hpp"

using std::set;

CreatureGenerationValues::CreatureGenerationValues()
: friendly(false),
danger_level(0), 
rarity(RARITY_COMMON), 
base_experience_value(0)
{
}

CreatureGenerationValues::~CreatureGenerationValues()
{
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

void CreatureGenerationValues::set_danger_level(const uint new_danger_level)
{
  danger_level = new_danger_level;
}

uint CreatureGenerationValues::get_danger_level() const
{
  return danger_level;
}

void CreatureGenerationValues::set_rarity(const Rarity new_rarity)
{
  rarity = new_rarity;
}

Rarity CreatureGenerationValues::get_rarity() const
{
  return rarity;
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
