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
soak_modifier(0)
{
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
soak_modifier(0)
{
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
soak_modifier(0)
{
  int size = args.size();

  // Fall through is intentional to allow setting all values from a given
  // size of the vector.
  switch (size)
  {
    default:
    case 9:
      soak_modifier = args.at(8);
    case 8:
      evade_modifier = args.at(7);
    case 7:
      charisma_modifier = args.at(6);
    case 6:
      willpower_modifier = args.at(5);
    case 5:
      intelligence_modifier = args.at(4);
    case 4:
      health_modifier = args.at(3);
    case 3:
      agility_modifier = args.at(2);
    case 2:
      dexterity_modifier = args.at(1);
    case 1:
      strength_modifier = args.at(0);
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
  result = result && statuses == m.statuses;

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

void Modifier::set_status(const string& status, const bool value)
{
  statuses[status] = value;
}

bool Modifier::has_status(const string& status_id) const
{
  auto s_it = statuses.find(status_id);

  return (s_it != statuses.end());
}

bool Modifier::get_status(const string& status_id) const
{
  bool val = false;

  auto s_it = statuses.find(status_id);

  if (s_it != statuses.end())
  {
    val = s_it->second;
  }

  return val;
}

vector<string> Modifier::get_affected_status_keys() const
{
  vector<string> status_keys;

  for (const auto& map_pair : statuses)
  {
    if (map_pair.second == true)
    {
      status_keys.push_back(map_pair.first);
    }
  }

  return status_keys;
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
          soak_modifier};
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

  size_t statuses_size = statuses.size();
  Serialize::write_size_t(stream, statuses_size);
  for (const auto& s_pair : statuses)
  {
    Serialize::write_string(stream, s_pair.first);
    Serialize::write_bool(stream, s_pair.second);
  }

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

  size_t statuses_size = 0;
  Serialize::read_size_t(stream, statuses_size);

  for (size_t i = 0; i < statuses_size; i++)
  {
    string status;
    bool value = false;

    Serialize::read_string(stream, status);
    Serialize::read_bool(stream, value);

    statuses.insert(make_pair(status, value));
  }

  return true;
}

ClassIdentifier Modifier::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MODIFIER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Modifier_test.cpp"
#endif