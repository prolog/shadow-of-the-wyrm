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

bool CreatureGenerationValues::operator==(const CreatureGenerationValues& cgv) const
{
  bool result = true;

  result = result && GenerationValues::operator==(cgv);

  result = result && (id == cgv.id);
  result = result && (race_id == cgv.race_id);
  result = result && (allowable_terrain_types == cgv.allowable_terrain_types);
  result = result && (friendly == cgv.friendly);
  result = result && (initial_hit_points == cgv.initial_hit_points);
  result = result && (initial_arcana_points == cgv.initial_arcana_points);
  result = result && (base_experience_value == cgv.base_experience_value);
  result = result && (skills == cgv.skills);
  result = result && (initial_equipment == cgv.initial_equipment);
  result = result && (initial_inventory == cgv.initial_inventory);
  result = result && (generator_filters == cgv.generator_filters);

  return result;
}

void CreatureGenerationValues::set_id(const std::string& new_id)
{
  id = new_id;
}

string CreatureGenerationValues::get_id() const
{
  return id;
}

void CreatureGenerationValues::set_race_id(const string& new_race_id)
{
  race_id = new_race_id;
}

string CreatureGenerationValues::get_race_id() const
{
  return race_id;
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

void CreatureGenerationValues::set_initial_arcana_points(const Dice& new_initial_arcana_points)
{
  initial_arcana_points = new_initial_arcana_points;
}

Dice CreatureGenerationValues::get_initial_arcana_points() const
{
  return initial_arcana_points;
}

void CreatureGenerationValues::set_base_experience_value(const uint new_base_experience)
{
  base_experience_value = new_base_experience;
}

uint CreatureGenerationValues::get_base_experience_value() const
{
  return base_experience_value;
}

void CreatureGenerationValues::set_skills(const Skills& new_skills)
{
  skills = new_skills;
}

Skills CreatureGenerationValues::get_skills() const
{
  return skills;
}

void CreatureGenerationValues::set_initial_equipment(const map<EquipmentWornLocation, InitialItem>& new_initial_equipment)
{
  initial_equipment = new_initial_equipment;
}

map<EquipmentWornLocation, InitialItem> CreatureGenerationValues::get_initial_equipment() const
{
  return initial_equipment;
}

void CreatureGenerationValues::set_initial_inventory(const vector<InitialItem>& new_initial_inventory)
{
  initial_inventory = new_initial_inventory;
}

vector<InitialItem> CreatureGenerationValues::get_initial_inventory() const
{
  return initial_inventory;
}

void CreatureGenerationValues::set_generator_filters(const vector<string>& new_generator_filters)
{
  generator_filters = new_generator_filters;
}

vector<string> CreatureGenerationValues::get_generator_filters() const
{
  return generator_filters;
}

bool CreatureGenerationValues::serialize(ostream& stream) const
{
  GenerationValues::serialize(stream);

  Serialize::write_string(stream, id);
  Serialize::write_string(stream, race_id);

  size_t terrain_types_size = allowable_terrain_types.size();
  Serialize::write_size_t(stream, terrain_types_size);

  if (terrain_types_size > 0)
  {
    for (const TileType allowable_type : allowable_terrain_types)
    {
      Serialize::write_enum(stream, allowable_type);
    }
  }

  Serialize::write_bool(stream, friendly);
  initial_hit_points.serialize(stream);
  initial_arcana_points.serialize(stream);
  Serialize::write_uint(stream, base_experience_value);

  // Initial Equipment
  size_t eq_map_size = initial_equipment.size();
  Serialize::write_size_t(stream, eq_map_size);

  for (const auto& initial_eq_pair : initial_equipment)
  {
    Serialize::write_enum(stream, initial_eq_pair.first);
    initial_eq_pair.second.serialize(stream);
  }

  // Initial Inventory
  size_t inv_size = initial_inventory.size();
  Serialize::write_size_t(stream, inv_size);

  for (const auto& item : initial_inventory)
  {
    item.serialize(stream);
  }

  Serialize::write_string_vector(stream, generator_filters);

  return true;
}

bool CreatureGenerationValues::deserialize(istream& stream)
{
  GenerationValues::deserialize(stream);

  Serialize::read_string(stream, id);
  Serialize::read_string(stream, race_id);

  size_t terrain_types_size = 0;
  Serialize::read_size_t(stream, terrain_types_size);

  if (terrain_types_size > 0)
  {
    allowable_terrain_types.clear();

    for (unsigned int i = 0; i < terrain_types_size; i++)
    {
      TileType allowable_type = TileType::TILE_TYPE_UNDEFINED;
      Serialize::read_enum(stream, allowable_type);

      allowable_terrain_types.insert(allowable_type);
    }
  }

  Serialize::read_bool(stream, friendly);
  initial_hit_points.deserialize(stream);
  initial_arcana_points.deserialize(stream);
  Serialize::read_uint(stream, base_experience_value);

  // Initial Equipment
  size_t eq_map_size = 0;
  Serialize::read_size_t(stream, eq_map_size);
  initial_equipment.clear();

  for (size_t i = 0; i < eq_map_size; i++)
  {
    EquipmentWornLocation ewl = EquipmentWornLocation::EQUIPMENT_WORN_HEAD;
    Serialize::read_enum(stream, ewl);

    InitialItem ii;
    ii.deserialize(stream);

    initial_equipment.insert(make_pair(ewl, ii));
  }

  size_t inv_size = 0;
  Serialize::read_size_t(stream, inv_size);
  initial_inventory.clear();

  for (size_t i = 0; i < inv_size; i++)
  {
    InitialItem ii;
    ii.deserialize(stream);

    initial_inventory.push_back(ii);
  }

  generator_filters.clear();
  Serialize::read_string_vector(stream, generator_filters);

  return true;
}

ClassIdentifier CreatureGenerationValues::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CREATURE_GENERATION_VALUES;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureGenerationValues_test.cpp"
#endif
