#include <sstream>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
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
  value = 1.0;
}

bool Resistance::operator==(const Resistance& r)
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

bool Resistance::serialize(ostream& stream)
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

bool Resistances::operator==(const Resistances& res)
{
  bool result = true;

  result = result && (resistances.size() == res.resistances.size());

  if (result)
  {
    ResistancesMap r2_map = res.resistances;
    ResistancesMap::iterator r_it;
    ResistancesMap::iterator r_it2;

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

bool Resistances::serialize(ostream& stream)
{
  Serialize::write_size_t(stream, resistances.size());

  BOOST_FOREACH(ResistancesMap::value_type& r_pair, resistances)
  {
    Serialize::write_enum(stream, r_pair.first);

    boost::shared_ptr<Resistance> resistance = r_pair.second;

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
      boost::shared_ptr<Resistance> resistance = ResistanceFactory::create_resistance(resistance_clid);
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

MentalResistance::MentalResistance()
: Resistance(DAMAGE_TYPE_MENTAL, ResistanceTextKeys::RESISTANCE_MENTAL, 0.0)
{
}

Resistance* MentalResistance::clone()
{
  return new MentalResistance(*this);
}

ClassIdentifier MentalResistance::internal_class_identifier() const
{
  return CLASS_ID_MENTAL_RESISTANCE;
}

SonicResistance::SonicResistance()
: Resistance(DAMAGE_TYPE_SONIC, ResistanceTextKeys::RESISTANCE_SONIC, 0.0)
{
}

Resistance* SonicResistance::clone()
{
  return new SonicResistance(*this);
}

ClassIdentifier SonicResistance::internal_class_identifier() const
{
  return CLASS_ID_SONIC_RESISTANCE;
}

RadiantResistance::RadiantResistance()
: Resistance(DAMAGE_TYPE_RADIANT, ResistanceTextKeys::RESISTANCE_RADIANT, 0.0)
{
}

Resistance* RadiantResistance::clone()
{
  return new RadiantResistance(*this);
}

ClassIdentifier RadiantResistance::internal_class_identifier() const
{
  return CLASS_ID_RADIANT_RESISTANCE;
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
    boost::shared_ptr<Resistance> current_resistance = res_it->second;

    resistances_str = resistances_str + current_resistance->str() + " ";
  }

  return resistances_str;
}

// Reset the resistances to an absolute default - 1.0 for each value
void Resistances::default_resistances()
{
  boost::shared_ptr<Resistance> slash = boost::make_shared<SlashResistance>();
  boost::shared_ptr<Resistance> pound = boost::make_shared<PoundResistance>();
  boost::shared_ptr<Resistance> pierce = boost::make_shared<PierceResistance>();
  boost::shared_ptr<Resistance> heat = boost::make_shared<HeatResistance>();
  boost::shared_ptr<Resistance> cold = boost::make_shared<ColdResistance>();
  boost::shared_ptr<Resistance> acid = boost::make_shared<AcidResistance>();
  boost::shared_ptr<Resistance> poison = boost::make_shared<PoisonResistance>();
  boost::shared_ptr<Resistance> holy = boost::make_shared<HolyResistance>();
  boost::shared_ptr<Resistance> shadow = boost::make_shared<ShadowResistance>();
  boost::shared_ptr<Resistance> arcane = boost::make_shared<ArcaneResistance>();
  boost::shared_ptr<Resistance> mental = boost::make_shared<MentalResistance>();
  boost::shared_ptr<Resistance> sonic = boost::make_shared<SonicResistance>();
  boost::shared_ptr<Resistance> radiant = boost::make_shared<RadiantResistance>();
  boost::shared_ptr<Resistance> lightning = boost::make_shared<LightningResistance>();

  resistances.clear();

  resistances.insert(make_pair(DAMAGE_TYPE_SLASH, slash));
  resistances.insert(make_pair(DAMAGE_TYPE_POUND, pound));
  resistances.insert(make_pair(DAMAGE_TYPE_PIERCE, pierce));
  resistances.insert(make_pair(DAMAGE_TYPE_HEAT, heat));
  resistances.insert(make_pair(DAMAGE_TYPE_COLD, cold));
  resistances.insert(make_pair(DAMAGE_TYPE_ACID, acid));
  resistances.insert(make_pair(DAMAGE_TYPE_POISON, poison));
  resistances.insert(make_pair(DAMAGE_TYPE_HOLY, holy));
  resistances.insert(make_pair(DAMAGE_TYPE_SHADOW, shadow));
  resistances.insert(make_pair(DAMAGE_TYPE_ARCANE, arcane));
  resistances.insert(make_pair(DAMAGE_TYPE_MENTAL, mental));
  resistances.insert(make_pair(DAMAGE_TYPE_SONIC, sonic));
  resistances.insert(make_pair(DAMAGE_TYPE_RADIANT, radiant));
  resistances.insert(make_pair(DAMAGE_TYPE_LIGHTNING, lightning));
}

#ifdef UNIT_TESTS
#include "unit_tests/Resistances_test.cpp"
#endif


