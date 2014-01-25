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
  type = DAMAGE_TYPE_NULL;
  name_sid = "";
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
  result = result && (dequal(value, r.value));

  return result;
}

Resistance::Resistance(const DamageType dt, const string& name, const double val)
{
  type = dt;
  name_sid = name;
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
  Serialize::write_double(stream, value);

  return true;
}

bool Resistance::deserialize(istream& stream)
{
  Serialize::read_enum(stream, type);
  Serialize::read_string(stream, name_sid);
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
  for (DamageType dt = DAMAGE_TYPE_SLASH; dt < DAMAGE_TYPE_MAX; dt++)
  {
    resistances[dt]->set_value(value);
  }
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
      Serialize::write_class_id(stream, CLASS_ID_NULL);
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
    DamageType type = DAMAGE_TYPE_SLASH;
    Serialize::read_enum(stream, type);

    ClassIdentifier resistance_clid = CLASS_ID_NULL;
    Serialize::read_class_id(stream, resistance_clid);

    if (resistance_clid != CLASS_ID_NULL)
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
  return CLASS_ID_RESISTANCES;
}

// Individual resistance classes
SlashResistance::SlashResistance()
: Resistance(DAMAGE_TYPE_SLASH, ResistanceTextKeys::RESISTANCE_SLASH, 0.0)
{
}

Resistance* SlashResistance::clone()
{
  return new SlashResistance(*this);
}

ClassIdentifier SlashResistance::internal_class_identifier() const
{
  return CLASS_ID_SLASH_RESISTANCE;
}

PoundResistance::PoundResistance()
: Resistance(DAMAGE_TYPE_POUND, ResistanceTextKeys::RESISTANCE_POUND, 0.0)
{
}

Resistance* PoundResistance::clone()
{
  return new PoundResistance(*this);
}

ClassIdentifier PoundResistance::internal_class_identifier() const
{
  return CLASS_ID_POUND_RESISTANCE;
}

PierceResistance::PierceResistance()
: Resistance(DAMAGE_TYPE_PIERCE, ResistanceTextKeys::RESISTANCE_PIERCE, 0.0)
{
}

Resistance* PierceResistance::clone()
{
  return new PierceResistance(*this);
}

ClassIdentifier PierceResistance::internal_class_identifier() const
{
  return CLASS_ID_PIERCE_RESISTANCE;
}

HeatResistance::HeatResistance()
: Resistance(DAMAGE_TYPE_HEAT, ResistanceTextKeys::RESISTANCE_HEAT, 0.0)
{
}

Resistance* HeatResistance::clone()
{
  return new HeatResistance(*this);
}

ClassIdentifier HeatResistance::internal_class_identifier() const
{
  return CLASS_ID_HEAT_RESISTANCE;
}

ColdResistance::ColdResistance()
: Resistance(DAMAGE_TYPE_COLD, ResistanceTextKeys::RESISTANCE_COLD, 0.0)
{
}

Resistance* ColdResistance::clone()
{
  return new ColdResistance(*this);
}

ClassIdentifier ColdResistance::internal_class_identifier() const
{
  return CLASS_ID_COLD_RESISTANCE;
}

AcidResistance::AcidResistance()
: Resistance(DAMAGE_TYPE_ACID, ResistanceTextKeys::RESISTANCE_ACID, 0.0)
{
}

Resistance* AcidResistance::clone()
{
  return new AcidResistance(*this);
}

ClassIdentifier AcidResistance::internal_class_identifier() const
{
  return CLASS_ID_ACID_RESISTANCE;
}

PoisonResistance::PoisonResistance()
: Resistance(DAMAGE_TYPE_POISON, ResistanceTextKeys::RESISTANCE_POISON, 0.0)
{
}

Resistance* PoisonResistance::clone()
{
  return new PoisonResistance(*this);
}

ClassIdentifier PoisonResistance::internal_class_identifier() const
{
  return CLASS_ID_POISON_RESISTANCE;
}

HolyResistance::HolyResistance()
: Resistance(DAMAGE_TYPE_HOLY, ResistanceTextKeys::RESISTANCE_HOLY, 0.0)
{
}

Resistance* HolyResistance::clone()
{
  return new HolyResistance(*this);
}

ClassIdentifier HolyResistance::internal_class_identifier() const
{
  return CLASS_ID_HOLY_RESISTANCE;
}

ShadowResistance::ShadowResistance()
: Resistance(DAMAGE_TYPE_SHADOW, ResistanceTextKeys::RESISTANCE_SHADOW, 0.0)
{
}

Resistance* ShadowResistance::clone()
{
  return new ShadowResistance(*this);
}

ClassIdentifier ShadowResistance::internal_class_identifier() const
{
  return CLASS_ID_SHADOW_RESISTANCE;
}

ArcaneResistance::ArcaneResistance()
: Resistance(DAMAGE_TYPE_ARCANE, ResistanceTextKeys::RESISTANCE_ARCANE, 0.0)
{
}

Resistance* ArcaneResistance::clone()
{
  return new ArcaneResistance(*this);
}

ClassIdentifier ArcaneResistance::internal_class_identifier() const
{
  return CLASS_ID_ARCANE_RESISTANCE;
}

LightningResistance::LightningResistance()
: Resistance(DAMAGE_TYPE_LIGHTNING, ResistanceTextKeys::RESISTANCE_LIGHTNING, 0.0)
{
}

Resistance* LightningResistance::clone()
{
  return new LightningResistance(*this);
}

ClassIdentifier LightningResistance::internal_class_identifier() const
{
  return CLASS_ID_LIGHTNING_RESISTANCE;
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
  resistances = ResistancesMap{{DAMAGE_TYPE_SLASH, slash},
                               {DAMAGE_TYPE_POUND, pound},
                               {DAMAGE_TYPE_PIERCE, pierce},
                               {DAMAGE_TYPE_HEAT, heat},
                               {DAMAGE_TYPE_COLD, cold},
                               {DAMAGE_TYPE_ACID, acid},
                               {DAMAGE_TYPE_POISON, poison},
                               {DAMAGE_TYPE_HOLY, holy},
                               {DAMAGE_TYPE_SHADOW, shadow},
                               {DAMAGE_TYPE_ARCANE, arcane},
                               {DAMAGE_TYPE_LIGHTNING, lightning}};
}

#ifdef UNIT_TESTS
#include "unit_tests/Resistances_test.cpp"
#endif


