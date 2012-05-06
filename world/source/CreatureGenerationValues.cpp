#include "CreatureGenerationValues.hpp"

using std::set;

CreatureGenerationValues::CreatureGenerationValues()
: danger_level(0), rarity(RARITY_COMMON)
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
