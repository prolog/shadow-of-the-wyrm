#include <sstream>
#include "global_prototypes.hpp"
#include "Resistances.hpp"
#include "ResistanceTextKeys.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;

// Initialize the Resistance

// By default, the multiplier should be 1.
// This is because creatures without a race
// and class will use this value, so they
// should have absolutely no vulnerabilities
// or resistances.
Resistance::Resistance()
: type(DamageType::DAMAGE_TYPE_NULL)
, value(1.0)
{
}

Resistance::Resistance(const DamageType dt, const string& name, const string& abrv, const string& gain, const string& lose, const double val)
: type(dt), name_sid(name), abrv_sid(abrv), gain_message_sid(gain), lose_message_sid(lose), value(val)
{
}

bool Resistance::operator==(const Resistance& r) const
{
  bool result = true;

  result = result && (type == r.type);
  result = result && (name_sid == r.name_sid);
  result = result && (abrv_sid == r.abrv_sid);
  result = result && (gain_message_sid == r.gain_message_sid);
  result = result && (lose_message_sid == r.lose_message_sid);
  result = result && (dequal(value, r.value));

  return result;
}

void Resistance::set_type(const DamageType new_type)
{
  type = new_type;
}

DamageType Resistance::get_type() const
{
  return type;
}

void Resistance::set_name_sid(const string& new_name_sid)
{
  name_sid = new_name_sid;
}

string Resistance::get_name_sid() const
{
  return name_sid;
}

void Resistance::set_abrv_sid(const string& new_abrv_sid)
{
  abrv_sid = new_abrv_sid;
}

string Resistance::get_abrv_sid() const
{
  return abrv_sid;
}

string Resistance::get_gain_or_lose_message_sid(const bool gained_resistance) const
{
  if (gained_resistance)
  {
    return gain_message_sid;
  }
  else
  {
    return lose_message_sid;
  }
}

void Resistance::set_gain_message_sid(const string& new_msg_sid)
{
  gain_message_sid = new_msg_sid;
}

string Resistance::get_gain_message_sid() const
{
  return gain_message_sid;
}

void Resistance::set_lose_message_sid(const string& new_msg_sid)
{
  lose_message_sid = new_msg_sid;
}

string Resistance::get_lose_message_sid() const
{
  return lose_message_sid;
}

void Resistance::set_value(const double new_value)
{
  value = new_value;
}

double Resistance::get_value() const
{
  return value;
}

string Resistance::get_value_str() const
{
  stringstream ss;
  ss.precision(2);

  ss << fixed << value;
  return ss.str();
}

// Used only for testing/debug purposes (stub tester, etc).
string Resistance::str() const
{
  ostringstream ss;

  ss << StringTable::get(name_sid) << ": " << value;

  return ss.str();
}

ClassIdentifier Resistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_RESISTANCE;
}

bool Resistance::serialize(ostream& stream) const
{
  Serialize::write_enum(stream, type);
  Serialize::write_string(stream, name_sid);
  Serialize::write_string(stream, abrv_sid);
  Serialize::write_string(stream, gain_message_sid);
  Serialize::write_string(stream, lose_message_sid);
  Serialize::write_double(stream, value);

  return true;
}

bool Resistance::deserialize(istream& stream)
{
  Serialize::read_enum(stream, type);
  Serialize::read_string(stream, name_sid);
  Serialize::read_string(stream, abrv_sid);
  Serialize::read_string(stream, gain_message_sid);
  Serialize::read_string(stream, lose_message_sid);
  Serialize::read_double(stream, value);

  return true;
}

// Initialize the resistances to a set of default values
Resistances::Resistances()
{
  default_resistances();
}

Resistances::Resistances(const Resistances& r)
{
  *this = r;
}

bool Resistances::operator==(const Resistances& r) const
{
  return resistances == r.resistances;
}

void Resistances::clear()
{
  resistances.clear();
}

void Resistances::add(const Resistances& res)
{
  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    double new_resistance_value = get_resistance_value(dt) + res.get_resistance_value(dt);
    set_resistance_value(dt, new_resistance_value);
  }
}

void Resistances::set_resistance_value(const DamageType type, double value)
{
  resistances[type].set_value(value);
}

void Resistances::set_all_resistances_to(const double value)
{
  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    resistances[dt].set_value(value);
  }
}

const Resistance& Resistances::get_resistance_cref(const DamageType dt) const
{
  return resistances.find(dt)->second;
}

Resistance& Resistances::get_resistance_ref(const DamageType dt)
{
  return resistances[dt];
}

bool Resistances::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, resistances.size());

  for (const ResistancesMap::value_type& r_pair : resistances)
  {
    Serialize::write_enum(stream, r_pair.first);
    Resistance r = r_pair.second;

    Serialize::write_class_id(stream, r.get_class_identifier());
    r.serialize(stream);
  }

  return true;
}

bool Resistances::deserialize(istream& stream)
{
  size_t resistances_size = 0;
  Serialize::read_size_t(stream, resistances_size);

  for (unsigned int i = 0; i < resistances_size; i++)
  {
    DamageType type = DamageType::DAMAGE_TYPE_FIRST;
    Serialize::read_enum(stream, type);

    ClassIdentifier resistance_clid = ClassIdentifier::CLASS_ID_NULL;
    Serialize::read_class_id(stream, resistance_clid);

    if (resistance_clid != ClassIdentifier::CLASS_ID_NULL)
    {
      Resistance new_res;

      if (!new_res.deserialize(stream))
      {
        return false;
      }

      resistances[type] = new_res;
    }
  }
  return true;
}

ClassIdentifier Resistances::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_RESISTANCES;
}

bool Resistances::has_resistances_or_vulnerabilities() const
{
  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);

    double val = get_resistance_value(dt);

    if (!dequal(val, 0.00))
    {
      return true;
    }
  }
  
  return false;
}

double Resistances::get_total() const
{
  double total = 0.0;

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    total += get_resistance_value(dt);
  }

  return total;
}

double Resistances::get_resistance_value(const DamageType type) const
{
  ResistancesMap::const_iterator map_it = resistances.find(type);

  if (map_it != resistances.end())
  {
    return (map_it->second).get_value();
  }

  return DEFAULT_RESISTANCE_VALUE;
}

ResistancesMap Resistances::get_resistances_map() const
{
  return resistances;
}

string Resistances::str() const
{
  string resistances_str;

  for (ResistancesMap::const_iterator res_it = resistances.begin(); res_it != resistances.end(); res_it++)
  {
    Resistance current_resistance = res_it->second;

    resistances_str = resistances_str + current_resistance.str() + " ";
  }

  return resistances_str;
}

void Resistances::default_resistances()
{
  resistances = { { DamageType::DAMAGE_TYPE_SLASH,     Resistance(DamageType::DAMAGE_TYPE_SLASH, ResistanceTextKeys::RESISTANCE_SLASH, ResistanceTextKeys::RESISTANCE_ABRV_SLASH, ResistanceTextKeys::RESISTANCE_GAIN_SLASH, ResistanceTextKeys::RESISTANCE_LOSE_SLASH, 0.0) },
                  { DamageType::DAMAGE_TYPE_POUND,     Resistance(DamageType::DAMAGE_TYPE_POUND, ResistanceTextKeys::RESISTANCE_POUND, ResistanceTextKeys::RESISTANCE_ABRV_POUND, ResistanceTextKeys::RESISTANCE_GAIN_POUND, ResistanceTextKeys::RESISTANCE_LOSE_POUND, 0.0) },
                  { DamageType::DAMAGE_TYPE_PIERCE,    Resistance(DamageType::DAMAGE_TYPE_PIERCE, ResistanceTextKeys::RESISTANCE_PIERCE, ResistanceTextKeys::RESISTANCE_ABRV_PIERCE, ResistanceTextKeys::RESISTANCE_GAIN_PIERCE, ResistanceTextKeys::RESISTANCE_LOSE_PIERCE, 0.0) },
                  { DamageType::DAMAGE_TYPE_HEAT,      Resistance(DamageType::DAMAGE_TYPE_HEAT, ResistanceTextKeys::RESISTANCE_HEAT, ResistanceTextKeys::RESISTANCE_ABRV_HEAT, ResistanceTextKeys::RESISTANCE_GAIN_HEAT, ResistanceTextKeys::RESISTANCE_LOSE_HEAT, 0.0) },
                  { DamageType::DAMAGE_TYPE_COLD,      Resistance(DamageType::DAMAGE_TYPE_COLD, ResistanceTextKeys::RESISTANCE_COLD, ResistanceTextKeys::RESISTANCE_ABRV_COLD, ResistanceTextKeys::RESISTANCE_GAIN_COLD, ResistanceTextKeys::RESISTANCE_LOSE_COLD, 0.0) },
                  { DamageType::DAMAGE_TYPE_ACID,      Resistance(DamageType::DAMAGE_TYPE_ACID, ResistanceTextKeys::RESISTANCE_ACID, ResistanceTextKeys::RESISTANCE_ABRV_ACID, ResistanceTextKeys::RESISTANCE_GAIN_ACID, ResistanceTextKeys::RESISTANCE_LOSE_ACID, 0.0) },
                  { DamageType::DAMAGE_TYPE_POISON,    Resistance(DamageType::DAMAGE_TYPE_POISON, ResistanceTextKeys::RESISTANCE_POISON, ResistanceTextKeys::RESISTANCE_ABRV_POISON, ResistanceTextKeys::RESISTANCE_GAIN_POISON, ResistanceTextKeys::RESISTANCE_LOSE_POISON, 0.0) },
                  { DamageType::DAMAGE_TYPE_HOLY,      Resistance(DamageType::DAMAGE_TYPE_HOLY, ResistanceTextKeys::RESISTANCE_HOLY, ResistanceTextKeys::RESISTANCE_ABRV_HOLY, ResistanceTextKeys::RESISTANCE_GAIN_HOLY, ResistanceTextKeys::RESISTANCE_LOSE_HOLY, 0.0) },
                  { DamageType::DAMAGE_TYPE_SHADOW,    Resistance(DamageType::DAMAGE_TYPE_SHADOW, ResistanceTextKeys::RESISTANCE_SHADOW, ResistanceTextKeys::RESISTANCE_ABRV_SHADOW, ResistanceTextKeys::RESISTANCE_GAIN_SHADOW, ResistanceTextKeys::RESISTANCE_LOSE_SHADOW, 0.0) },
                  { DamageType::DAMAGE_TYPE_ARCANE,    Resistance(DamageType::DAMAGE_TYPE_ARCANE, ResistanceTextKeys::RESISTANCE_ARCANE, ResistanceTextKeys::RESISTANCE_ABRV_ARCANE, ResistanceTextKeys::RESISTANCE_GAIN_ARCANE, ResistanceTextKeys::RESISTANCE_LOSE_ARCANE, 0.0)},
                  { DamageType::DAMAGE_TYPE_LIGHTNING, Resistance(DamageType::DAMAGE_TYPE_LIGHTNING, ResistanceTextKeys::RESISTANCE_LIGHTNING, ResistanceTextKeys::RESISTANCE_ABRV_LIGHTNING, ResistanceTextKeys::RESISTANCE_GAIN_LIGHTNING, ResistanceTextKeys::RESISTANCE_LOSE_LIGHTNING, 0.0) }
  };
}
#ifdef UNIT_TESTS
#include "unit_tests/Resistances_test.cpp"
#endif


