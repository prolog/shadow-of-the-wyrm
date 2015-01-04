#include <sstream>
#include "global_prototypes.hpp"
#include "Resistances.hpp"
#include "ResistanceFactory.hpp"
#include "ResistanceTextKeys.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;

// Initialize the Resistance
Resistance::Resistance()
{
  type = DamageType::DAMAGE_TYPE_NULL;

  // By default, the multiplier should be 1.
  // This is because creatures without a race
  // and class will use this value, so they
  // should have absolutely no vulnerabilities
  // or resistances.
  value = 1.0;
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

Resistance::Resistance(const DamageType dt, const string& name, const string& abrv, const string& gain, const string& lose, const double val)
{
  type = dt;
  name_sid = name;
  abrv_sid = abrv;
  gain_message_sid = gain;
  lose_message_sid = lose;
  value = val;
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

// Used only for testing/debug purposes (stub tester, etc).
string Resistance::str() const
{
  ostringstream ss;

  ss << StringTable::get(name_sid) << ": " << value;

  return ss.str();
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

bool Resistances::operator==(const Resistances& res) const
{
  bool result = true;

  result = result && (resistances.size() == res.resistances.size());

  if (result)
  {
    ResistancesMap r2_map = res.resistances;
    ResistancesMap::const_iterator r_it;
    ResistancesMap::const_iterator r_it2;

    r_it = resistances.begin();
    r_it2 = r2_map.begin();

    while (r_it != resistances.end())
    {
      result = result && (*r_it->second == *r_it2->second);

      if (!result) break;

      r_it++;
      r_it2++;
    }
  }

  return result;
}

void Resistances::set_resistance_value(const DamageType type, double value)
{
  resistances[type]->set_value(value);
}

void Resistances::set_all_resistances_to(const double value)
{
  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    resistances[dt]->set_value(value);
  }
}

ResistancePtr Resistances::get_resistance(const DamageType dt) const
{
  ResistancePtr res = resistances.find(dt)->second;
  return res;
}

bool Resistances::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, resistances.size());

  for (const ResistancesMap::value_type& r_pair : resistances)
  {
    Serialize::write_enum(stream, r_pair.first);

    std::shared_ptr<Resistance> resistance = r_pair.second;

    if (resistance)
    {
      Serialize::write_class_id(stream, resistance->get_class_identifier());
      resistance->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
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
      std::shared_ptr<Resistance> resistance = ResistanceFactory::create_resistance(resistance_clid);
      if (!resistance) return false;
      if (!resistance->deserialize(stream)) return false;

      resistances[type] = resistance;
    }
  }
  return true;
}

ClassIdentifier Resistances::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_RESISTANCES;
}

// Individual resistance classes
SlashResistance::SlashResistance()
: Resistance(DamageType::DAMAGE_TYPE_SLASH, ResistanceTextKeys::RESISTANCE_SLASH, ResistanceTextKeys::RESISTANCE_ABRV_SLASH, ResistanceTextKeys::RESISTANCE_GAIN_SLASH, ResistanceTextKeys::RESISTANCE_LOSE_SLASH, 0.0)
{
}

Resistance* SlashResistance::clone()
{
  return new SlashResistance(*this);
}

ClassIdentifier SlashResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SLASH_RESISTANCE;
}

PoundResistance::PoundResistance()
: Resistance(DamageType::DAMAGE_TYPE_POUND, ResistanceTextKeys::RESISTANCE_POUND, ResistanceTextKeys::RESISTANCE_ABRV_POUND, ResistanceTextKeys::RESISTANCE_GAIN_POUND, ResistanceTextKeys::RESISTANCE_LOSE_POUND, 0.0)
{
}

Resistance* PoundResistance::clone()
{
  return new PoundResistance(*this);
}

ClassIdentifier PoundResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_POUND_RESISTANCE;
}

PierceResistance::PierceResistance()
: Resistance(DamageType::DAMAGE_TYPE_PIERCE, ResistanceTextKeys::RESISTANCE_PIERCE, ResistanceTextKeys::RESISTANCE_ABRV_PIERCE, ResistanceTextKeys::RESISTANCE_GAIN_PIERCE, ResistanceTextKeys::RESISTANCE_LOSE_PIERCE, 0.0)
{
}

Resistance* PierceResistance::clone()
{
  return new PierceResistance(*this);
}

ClassIdentifier PierceResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PIERCE_RESISTANCE;
}

HeatResistance::HeatResistance()
: Resistance(DamageType::DAMAGE_TYPE_HEAT, ResistanceTextKeys::RESISTANCE_HEAT, ResistanceTextKeys::RESISTANCE_ABRV_HEAT, ResistanceTextKeys::RESISTANCE_GAIN_HEAT, ResistanceTextKeys::RESISTANCE_LOSE_HEAT, 0.0)
{
}

Resistance* HeatResistance::clone()
{
  return new HeatResistance(*this);
}

ClassIdentifier HeatResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HEAT_RESISTANCE;
}

ColdResistance::ColdResistance()
: Resistance(DamageType::DAMAGE_TYPE_COLD, ResistanceTextKeys::RESISTANCE_COLD, ResistanceTextKeys::RESISTANCE_ABRV_COLD, ResistanceTextKeys::RESISTANCE_GAIN_COLD, ResistanceTextKeys::RESISTANCE_LOSE_COLD, 0.0)
{
}

Resistance* ColdResistance::clone()
{
  return new ColdResistance(*this);
}

ClassIdentifier ColdResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_COLD_RESISTANCE;
}

AcidResistance::AcidResistance()
: Resistance(DamageType::DAMAGE_TYPE_ACID, ResistanceTextKeys::RESISTANCE_ACID, ResistanceTextKeys::RESISTANCE_ABRV_ACID, ResistanceTextKeys::RESISTANCE_GAIN_ACID, ResistanceTextKeys::RESISTANCE_LOSE_ACID, 0.0)
{
}

Resistance* AcidResistance::clone()
{
  return new AcidResistance(*this);
}

ClassIdentifier AcidResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ACID_RESISTANCE;
}

PoisonResistance::PoisonResistance()
: Resistance(DamageType::DAMAGE_TYPE_POISON, ResistanceTextKeys::RESISTANCE_POISON, ResistanceTextKeys::RESISTANCE_ABRV_POISON, ResistanceTextKeys::RESISTANCE_GAIN_POISON, ResistanceTextKeys::RESISTANCE_LOSE_POISON, 0.0)
{
}

Resistance* PoisonResistance::clone()
{
  return new PoisonResistance(*this);
}

ClassIdentifier PoisonResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_POISON_RESISTANCE;
}

HolyResistance::HolyResistance()
: Resistance(DamageType::DAMAGE_TYPE_HOLY, ResistanceTextKeys::RESISTANCE_HOLY, ResistanceTextKeys::RESISTANCE_ABRV_HOLY, ResistanceTextKeys::RESISTANCE_GAIN_HOLY, ResistanceTextKeys::RESISTANCE_LOSE_HOLY, 0.0)
{
}

Resistance* HolyResistance::clone()
{
  return new HolyResistance(*this);
}

ClassIdentifier HolyResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HOLY_RESISTANCE;
}

ShadowResistance::ShadowResistance()
: Resistance(DamageType::DAMAGE_TYPE_SHADOW, ResistanceTextKeys::RESISTANCE_SHADOW, ResistanceTextKeys::RESISTANCE_ABRV_SHADOW, ResistanceTextKeys::RESISTANCE_GAIN_SHADOW, ResistanceTextKeys::RESISTANCE_LOSE_SHADOW, 0.0)
{
}

Resistance* ShadowResistance::clone()
{
  return new ShadowResistance(*this);
}

ClassIdentifier ShadowResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SHADOW_RESISTANCE;
}

ArcaneResistance::ArcaneResistance()
: Resistance(DamageType::DAMAGE_TYPE_ARCANE, ResistanceTextKeys::RESISTANCE_ARCANE, ResistanceTextKeys::RESISTANCE_ABRV_ARCANE, ResistanceTextKeys::RESISTANCE_GAIN_ARCANE, ResistanceTextKeys::RESISTANCE_LOSE_ARCANE, 0.0)
{
}

Resistance* ArcaneResistance::clone()
{
  return new ArcaneResistance(*this);
}

ClassIdentifier ArcaneResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ARCANE_RESISTANCE;
}

LightningResistance::LightningResistance()
: Resistance(DamageType::DAMAGE_TYPE_LIGHTNING, ResistanceTextKeys::RESISTANCE_LIGHTNING, ResistanceTextKeys::RESISTANCE_ABRV_LIGHTNING, ResistanceTextKeys::RESISTANCE_GAIN_LIGHTNING, ResistanceTextKeys::RESISTANCE_LOSE_LIGHTNING, 0.0)
{
}

Resistance* LightningResistance::clone()
{
  return new LightningResistance(*this);
}

ClassIdentifier LightningResistance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_LIGHTNING_RESISTANCE;
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

double Resistances::get_resistance_value(const DamageType type) const
{
  ResistancesMap::const_iterator map_it = resistances.find(type);

  if (map_it != resistances.end())
  {
    return (map_it->second)->get_value();
  }

  return DEFAULT_RESISTANCE_VALUE;
}

string Resistances::str() const
{
  string resistances_str;

  for (ResistancesMap::const_iterator res_it = resistances.begin(); res_it != resistances.end(); res_it++)
  {
    std::shared_ptr<Resistance> current_resistance = res_it->second;

    resistances_str = resistances_str + current_resistance->str() + " ";
  }

  return resistances_str;
}

// Reset the resistances to an absolute default - 1.0 for each value
void Resistances::default_resistances()
{
  std::shared_ptr<Resistance> slash = std::make_shared<SlashResistance>();
  std::shared_ptr<Resistance> pound = std::make_shared<PoundResistance>();
  std::shared_ptr<Resistance> pierce = std::make_shared<PierceResistance>();
  std::shared_ptr<Resistance> heat = std::make_shared<HeatResistance>();
  std::shared_ptr<Resistance> cold = std::make_shared<ColdResistance>();
  std::shared_ptr<Resistance> acid = std::make_shared<AcidResistance>();
  std::shared_ptr<Resistance> poison = std::make_shared<PoisonResistance>();
  std::shared_ptr<Resistance> holy = std::make_shared<HolyResistance>();
  std::shared_ptr<Resistance> shadow = std::make_shared<ShadowResistance>();
  std::shared_ptr<Resistance> arcane = std::make_shared<ArcaneResistance>();
  std::shared_ptr<Resistance> lightning = std::make_shared<LightningResistance>();

  resistances.clear();
  resistances = ResistancesMap{{DamageType::DAMAGE_TYPE_SLASH, slash},
                               {DamageType::DAMAGE_TYPE_POUND, pound},
                               {DamageType::DAMAGE_TYPE_PIERCE, pierce},
                               {DamageType::DAMAGE_TYPE_HEAT, heat},
                               {DamageType::DAMAGE_TYPE_COLD, cold},
                               {DamageType::DAMAGE_TYPE_ACID, acid},
                               {DamageType::DAMAGE_TYPE_POISON, poison},
                               {DamageType::DAMAGE_TYPE_HOLY, holy},
                               {DamageType::DAMAGE_TYPE_SHADOW, shadow},
                               {DamageType::DAMAGE_TYPE_ARCANE, arcane},
                               {DamageType::DAMAGE_TYPE_LIGHTNING, lightning}};
}

#ifdef UNIT_TESTS
#include "unit_tests/Resistances_test.cpp"
#endif


