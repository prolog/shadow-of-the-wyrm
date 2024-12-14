#include "Modifier.hpp"
#include "Serialize.hpp"

using namespace std;

// Default all the modifiers to 0.
Modifier::Modifier()
: strength_modifier(0),
dexterity_modifier(0),
agility_modifier(0),
health_modifier(0),
intelligence_modifier(0),
willpower_modifier(0),
charisma_modifier(0),
evade_modifier(0),
soak_modifier(0),
speed_modifier(0),
to_hit_modifier(0),
mark_delete(false),
permanent(false)
{
  resistances.set_all_resistances_to(0);
}

// Set actual values for the modifiers
Modifier::Modifier
(
  const int new_strength_modifier,
  const int new_dexterity_modifier,
  const int new_agility_modifier,
  const int new_health_modifier,
  const int new_intelligence_modifier,
  const int new_willpower_modifier,
  const int new_charisma_modifier
)
: strength_modifier(new_strength_modifier),
dexterity_modifier(new_dexterity_modifier),
agility_modifier(new_agility_modifier),
health_modifier(new_health_modifier),
intelligence_modifier(new_intelligence_modifier),
willpower_modifier(new_willpower_modifier),
charisma_modifier(new_charisma_modifier),
evade_modifier(0),
soak_modifier(0),
speed_modifier(0),
to_hit_modifier(0),
mark_delete(false),
permanent(false)
{
  resistances.set_all_resistances_to(0);
}

// Version called by the XML reader.
Modifier::Modifier(const vector<int>& args)
: strength_modifier(0),
dexterity_modifier(0),
agility_modifier(0),
health_modifier(0),
intelligence_modifier(0),
willpower_modifier(0),
charisma_modifier(0),
evade_modifier(0),
soak_modifier(0),
speed_modifier(0),
to_hit_modifier(0),
mark_delete(false),
permanent(false)
{
  int size = args.size();

  // Fall through is intentional to allow setting all values from a given
  // size of the vector.
  switch (size)
  {
    // Resistances can't be set this way.  Must be set using set_resistances()
    default:
    case 11:
      speed_modifier = args.at(10);
      [[fallthrough]];
    case 10:
      to_hit_modifier = args.at(9);
      [[fallthrough]];
    case 9:
      soak_modifier = args.at(8);
      [[fallthrough]];
    case 8:
      evade_modifier = args.at(7);
      [[fallthrough]];
    case 7:
      charisma_modifier = args.at(6);
      [[fallthrough]];
    case 6:
      willpower_modifier = args.at(5);
      [[fallthrough]];
    case 5:
      intelligence_modifier = args.at(4);
      [[fallthrough]];
    case 4:
      health_modifier = args.at(3);
      [[fallthrough]];
    case 3:
      agility_modifier = args.at(2);
      [[fallthrough]];
    case 2:
      dexterity_modifier = args.at(1);
      [[fallthrough]];
    case 1:
      strength_modifier = args.at(0);
      [[fallthrough]];
    case 0:
      break;
  }
}

bool Modifier::operator==(const Modifier& m) const
{
  bool result = true;

  result = result && strength_modifier == m.strength_modifier;
  result = result && dexterity_modifier == m.dexterity_modifier;
  result = result && agility_modifier == m.agility_modifier;
  result = result && health_modifier == m.health_modifier;
  result = result && intelligence_modifier == m.intelligence_modifier;
  result = result && willpower_modifier == m.willpower_modifier;
  result = result && charisma_modifier == m.charisma_modifier;
  result = result && evade_modifier == m.evade_modifier;
  result = result && soak_modifier == m.soak_modifier;
  result = result && speed_modifier == m.speed_modifier;
  result = result && to_hit_modifier == m.to_hit_modifier;
  result = result && statuses == m.statuses;
  result = result && mark_delete == m.mark_delete;
  result = result && permanent == m.permanent;

  return result;
}

// Set/get each individual modifier
void Modifier::set_strength_modifier(const int new_strength_modifier)
{
  strength_modifier = new_strength_modifier;
}

int Modifier::get_strength_modifier() const
{
  return strength_modifier;
}

void Modifier::set_dexterity_modifier(const int new_dexterity_modifier)
{
  dexterity_modifier = new_dexterity_modifier;
}

int Modifier::get_dexterity_modifier() const
{
  return dexterity_modifier;
}

void Modifier::set_agility_modifier(const int new_agility_modifier)
{
  agility_modifier = new_agility_modifier;
}

int Modifier::get_agility_modifier() const
{
  return agility_modifier;
}

void Modifier::set_health_modifier(const int new_health_modifier)
{
  health_modifier = new_health_modifier;
}

int Modifier::get_health_modifier() const
{
  return health_modifier;
}

void Modifier::set_intelligence_modifier(const int new_intelligence_modifier)
{
  intelligence_modifier = new_intelligence_modifier;
}

int Modifier::get_intelligence_modifier() const
{
  return intelligence_modifier;
}

void Modifier::set_willpower_modifier(const int new_willpower_modifier)
{
  willpower_modifier = new_willpower_modifier;
}

int Modifier::get_willpower_modifier() const
{
  return willpower_modifier;
}

void Modifier::set_charisma_modifier(const int new_charisma_modifier)
{
  charisma_modifier = new_charisma_modifier;
}

int Modifier::get_charisma_modifier() const
{
  return charisma_modifier;
}

void Modifier::set_evade_modifier(const int new_evade_modifier)
{
  evade_modifier = new_evade_modifier;
}

int Modifier::get_evade_modifier() const
{
  return evade_modifier;
}

void Modifier::set_soak_modifier(const int new_soak_modifier)
{
  soak_modifier = new_soak_modifier;
}

int Modifier::get_soak_modifier() const
{
  return soak_modifier;
}

void Modifier::set_speed_modifier(const int new_speed_modifier)
{
  speed_modifier = new_speed_modifier;
}

int Modifier::get_speed_modifier() const
{
  return speed_modifier;
}

void Modifier::set_to_hit_modifier(const int new_to_hit_modifier)
{
  to_hit_modifier = new_to_hit_modifier;
}

int Modifier::get_to_hit_modifier() const
{
  return to_hit_modifier;
}

void Modifier::set_resistances(const Resistances& new_resistances)
{
  resistances = new_resistances;
}

Resistances Modifier::get_resistances() const
{
  return resistances;
}

bool Modifier::is_negative() const
{
  bool neg = is_statistics_part_negative() || is_resistances_part_negative();

  return neg;
}

bool Modifier::is_statistics_part_negative() const
{
  int sum;

  sum = strength_modifier
    + dexterity_modifier
    + agility_modifier
    + health_modifier
    + intelligence_modifier
    + willpower_modifier
    + charisma_modifier
    + evade_modifier
    + soak_modifier
    + speed_modifier
    + to_hit_modifier;

  return (sum < 0);
}

bool Modifier::is_resistances_part_negative() const
{
  double total = 0.0;

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    total += resistances.get_resistance_value(dt);
  }

  return (total < 0);
}

void Modifier::set_status(const string& status, const bool value, const int danger_level)
{
  statuses[status] = make_pair(value, danger_level);
}

bool Modifier::has_status(const string& status_id) const
{
  auto s_it = statuses.find(status_id);

  return (s_it != statuses.end());
}

pair<bool, int> Modifier::get_status(const string& status_id) const
{
  pair<bool, int> val(false, 1);

  auto s_it = statuses.find(status_id);

  if (s_it != statuses.end())
  {
    val = s_it->second;
  }

  return val;
}

vector<pair<string, int>> Modifier::get_affected_statuses() const
{
  vector<pair<string, int>> status_keys_and_danger;

  for (const auto& map_pair : statuses)
  {
    if (map_pair.second.first == true)
    {
      status_keys_and_danger.push_back(make_pair(map_pair.first, map_pair.second.second));
    }
  }

  return status_keys_and_danger;
}

vector<int> Modifier::get_raw_values() const
{
  return {strength_modifier, 
          dexterity_modifier, 
          agility_modifier, 
          health_modifier, 
          intelligence_modifier, 
          willpower_modifier, 
          charisma_modifier, 
          evade_modifier, 
          soak_modifier,
          to_hit_modifier,
          speed_modifier};
}

// Should the modifier be marked for later deletion?
void Modifier::set_delete(const bool new_delete)
{
  mark_delete = new_delete;
}

bool Modifier::get_delete() const
{
  return mark_delete;
}

// Is the modifier permanent? (e.g., incorporeal for spirits)
void Modifier::set_permanent(const bool new_permanent)
{
  permanent = new_permanent;
}

bool Modifier::get_permanent() const
{
  return permanent;
}

void Modifier::set_item_id(const string& new_item_id)
{
  item_id = new_item_id;
}

string Modifier::get_item_id() const
{
  return item_id;
}

bool Modifier::serialize(ostream& stream) const
{
  Serialize::write_int(stream, strength_modifier);
  Serialize::write_int(stream, dexterity_modifier);
  Serialize::write_int(stream, agility_modifier);
  Serialize::write_int(stream, health_modifier);
  Serialize::write_int(stream, intelligence_modifier);
  Serialize::write_int(stream, willpower_modifier);
  Serialize::write_int(stream, charisma_modifier);
  Serialize::write_int(stream, evade_modifier);
  Serialize::write_int(stream, soak_modifier);
  Serialize::write_int(stream, speed_modifier);
  Serialize::write_int(stream, to_hit_modifier);

  size_t statuses_size = statuses.size();
  Serialize::write_size_t(stream, statuses_size);
  for (const auto& s_pair : statuses)
  {
    Serialize::write_string(stream, s_pair.first);
    Serialize::write_bool(stream, s_pair.second.first);
    Serialize::write_int(stream, s_pair.second.second);
  }

  resistances.serialize(stream);
  Serialize::write_bool(stream, mark_delete);
  Serialize::write_bool(stream, permanent);
  Serialize::write_string(stream, item_id);

  return true;
}

bool Modifier::deserialize(istream& stream)
{
  Serialize::read_int(stream, strength_modifier);
  Serialize::read_int(stream, dexterity_modifier);
  Serialize::read_int(stream, agility_modifier);
  Serialize::read_int(stream, health_modifier);
  Serialize::read_int(stream, intelligence_modifier);
  Serialize::read_int(stream, willpower_modifier);
  Serialize::read_int(stream, charisma_modifier);
  Serialize::read_int(stream, evade_modifier);
  Serialize::read_int(stream, soak_modifier);
  Serialize::read_int(stream, speed_modifier);
  Serialize::read_int(stream, to_hit_modifier);

  size_t statuses_size = 0;
  Serialize::read_size_t(stream, statuses_size);

  for (size_t i = 0; i < statuses_size; i++)
  {
    string status;
    bool value = false;
    int danger_level = 1;

    Serialize::read_string(stream, status);
    Serialize::read_bool(stream, value);
    Serialize::read_int(stream, danger_level);

    statuses.insert(make_pair(status, make_pair(value, danger_level)));
  }

  resistances.deserialize(stream);
  Serialize::read_bool(stream, mark_delete);
  Serialize::read_bool(stream, permanent);
  Serialize::read_string(stream, item_id);

  return true;
}

ClassIdentifier Modifier::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MODIFIER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Modifier_test.cpp"
#endif