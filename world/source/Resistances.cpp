#include <sstream>
#include "Resistances.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"

using namespace std;

// Initialize the Resistance
Resistance::Resistance()
{
  type = RESISTANCE_TYPE_NULL;
  name_sid = "";
  value = 0.0;
}

Resistance::Resistance(const ResistanceType rt, const string& name, const double val)
{
  type = rt;
  name_sid = name;
  value = val;
}

void Resistance::set_type(const ResistanceType new_type)
{
  type = new_type;
}

ResistanceType Resistance::get_type() const
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

// Initialize the resistances to a set of default values
Resistances::Resistances()
{
  default_resistances();
}

void Resistances::set_resistance_value(const ResistanceType type, double value)
{
  resistances[type].set_value(value);
}

// Individual resistance classes
SlashResistance::SlashResistance()
: Resistance(RESISTANCE_TYPE_SLASH, ResistanceTextKeys::RESISTANCE_SLASH, 0.0)
{
}

PoundResistance::PoundResistance()
: Resistance(RESISTANCE_TYPE_POUND, ResistanceTextKeys::RESISTANCE_POUND, 0.0)
{
}

PierceResistance::PierceResistance()
: Resistance(RESISTANCE_TYPE_PIERCE, ResistanceTextKeys::RESISTANCE_PIERCE, 0.0)
{
}

HeatResistance::HeatResistance()
: Resistance(RESISTANCE_TYPE_HEAT, ResistanceTextKeys::RESISTANCE_HEAT, 0.0)
{
}

ColdResistance::ColdResistance()
: Resistance(RESISTANCE_TYPE_COLD, ResistanceTextKeys::RESISTANCE_COLD, 0.0)
{
}

AcidResistance::AcidResistance()
: Resistance(RESISTANCE_TYPE_ACID, ResistanceTextKeys::RESISTANCE_ACID, 0.0)
{
}

PoisonResistance::PoisonResistance()
: Resistance(RESISTANCE_TYPE_POISON, ResistanceTextKeys::RESISTANCE_POISON, 0.0)
{
}

HolyResistance::HolyResistance()
: Resistance(RESISTANCE_TYPE_HOLY, ResistanceTextKeys::RESISTANCE_HOLY, 0.0)
{
}

ShadowResistance::ShadowResistance()
: Resistance(RESISTANCE_TYPE_SHADOW, ResistanceTextKeys::RESISTANCE_SHADOW, 0.0)
{
}

ArcaneResistance::ArcaneResistance()
: Resistance(RESISTANCE_TYPE_ARCANE, ResistanceTextKeys::RESISTANCE_ARCANE, 0.0)
{
}

MentalResistance::MentalResistance()
: Resistance(RESISTANCE_TYPE_MENTAL, ResistanceTextKeys::RESISTANCE_MENTAL, 0.0)
{
}

SonicResistance::SonicResistance()
: Resistance(RESISTANCE_TYPE_SONIC, ResistanceTextKeys::RESISTANCE_SONIC, 0.0)
{
}

RadiantResistance::RadiantResistance()
: Resistance(RESISTANCE_TYPE_RADIANT, ResistanceTextKeys::RESISTANCE_RADIANT, 0.0)
{
}

LightningResistance::LightningResistance()
: Resistance(RESISTANCE_TYPE_LIGHTNING, ResistanceTextKeys::RESISTANCE_LIGHTNING, 0.0)
{
}

double Resistances::get_resistance_value(const ResistanceType type) const
{
  ResistancesMap::const_iterator map_it = resistances.find(type);

  if (map_it != resistances.end())
  {
    return (map_it->second).get_value();
  }

  return DEFAULT_RESISTANCE_VALUE;
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

// Reset the resistances to an absolute default - 1.0 for each value
void Resistances::default_resistances()
{
  SlashResistance slash;
  PoundResistance pound;
  PierceResistance pierce;
  HeatResistance heat;
  ColdResistance cold;
  AcidResistance acid;
  PoisonResistance poison;
  HolyResistance holy;
  ShadowResistance shadow;
  ArcaneResistance arcane;
  MentalResistance mental;
  SonicResistance sonic;
  RadiantResistance radiant;
  LightningResistance lightning;

  resistances.clear();

  resistances.insert(make_pair(RESISTANCE_TYPE_SLASH, slash));
  resistances.insert(make_pair(RESISTANCE_TYPE_POUND, pound));
  resistances.insert(make_pair(RESISTANCE_TYPE_PIERCE, pierce));
  resistances.insert(make_pair(RESISTANCE_TYPE_HEAT, heat));
  resistances.insert(make_pair(RESISTANCE_TYPE_COLD, cold));
  resistances.insert(make_pair(RESISTANCE_TYPE_ACID, acid));
  resistances.insert(make_pair(RESISTANCE_TYPE_POISON, poison));
  resistances.insert(make_pair(RESISTANCE_TYPE_HOLY, holy));
  resistances.insert(make_pair(RESISTANCE_TYPE_SHADOW, shadow));
  resistances.insert(make_pair(RESISTANCE_TYPE_ARCANE, arcane));
  resistances.insert(make_pair(RESISTANCE_TYPE_MENTAL, mental));
  resistances.insert(make_pair(RESISTANCE_TYPE_SONIC, sonic));
  resistances.insert(make_pair(RESISTANCE_TYPE_RADIANT, radiant));
  resistances.insert(make_pair(RESISTANCE_TYPE_LIGHTNING, lightning));
}
