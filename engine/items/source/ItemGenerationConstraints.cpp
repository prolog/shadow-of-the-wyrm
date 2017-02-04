#include "ItemGenerationConstraints.hpp"

using namespace std;

ItemGenerationConstraints::ItemGenerationConstraints()
: min_danger_level(1), max_danger_level(1), rarity(Rarity::RARITY_COMMON), item_type_restrictions({}), min_value(-1)
{
}

ItemGenerationConstraints::ItemGenerationConstraints(const int new_min_danger_level, const int new_max_danger_level, const Rarity new_rarity, const vector<ItemType>& new_item_type_restrictions, const int new_min_value)
: min_danger_level(new_min_danger_level), max_danger_level(new_max_danger_level), rarity(new_rarity), item_type_restrictions(new_item_type_restrictions), min_value(new_min_value)
{
}

void ItemGenerationConstraints::set_min_danger_level(const int new_min_danger_level)
{
  min_danger_level = new_min_danger_level;
}

int ItemGenerationConstraints::get_min_danger_level() const
{
  return min_danger_level;
}

void ItemGenerationConstraints::set_max_danger_level(const int new_max_danger_level)
{
  max_danger_level = new_max_danger_level;
}

int ItemGenerationConstraints::get_max_danger_level() const
{
  return max_danger_level;
}

void ItemGenerationConstraints::set_rarity(const Rarity new_rarity)
{
  rarity = new_rarity;
}

Rarity ItemGenerationConstraints::get_rarity() const
{
  return rarity;
}

void ItemGenerationConstraints::set_item_type_restrictions(const vector<ItemType>& new_item_type_restrictions)
{
  item_type_restrictions = new_item_type_restrictions;
}

vector<ItemType> ItemGenerationConstraints::get_item_type_restrictions() const
{
  return item_type_restrictions;
}

void ItemGenerationConstraints::set_min_value(const int new_min_value)
{
  min_value = new_min_value;
}

int ItemGenerationConstraints::get_min_value() const
{
  return min_value;
}

