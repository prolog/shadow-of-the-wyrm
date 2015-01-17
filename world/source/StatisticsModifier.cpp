#include "StatisticsModifier.hpp"
#include "Serialize.hpp"

using namespace std;

// Default all the modifiers to 0.
StatisticsModifier::StatisticsModifier()
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
StatisticsModifier::StatisticsModifier
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
StatisticsModifier::StatisticsModifier(const vector<int>& args)
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

bool StatisticsModifier::operator==(const StatisticsModifier& sm) const
{
  bool result = true;

  result = result && strength_modifier == sm.strength_modifier;
  result = result && dexterity_modifier == sm.dexterity_modifier;
  result = result && agility_modifier == sm.agility_modifier;
  result = result && health_modifier == sm.health_modifier;
  result = result && intelligence_modifier == sm.intelligence_modifier;
  result = result && willpower_modifier == sm.willpower_modifier;
  result = result && charisma_modifier == sm.charisma_modifier;
  result = result && evade_modifier == sm.evade_modifier;
  result = result && soak_modifier == sm.soak_modifier;

  return result;
}

// Set/get each individual modifier
void StatisticsModifier::set_strength_modifier(const int new_strength_modifier)
{
  strength_modifier = new_strength_modifier;
}

int StatisticsModifier::get_strength_modifier() const
{
  return strength_modifier;
}

void StatisticsModifier::set_dexterity_modifier(const int new_dexterity_modifier)
{
  dexterity_modifier = new_dexterity_modifier;
}

int StatisticsModifier::get_dexterity_modifier() const
{
  return dexterity_modifier;
}

void StatisticsModifier::set_agility_modifier(const int new_agility_modifier)
{
  agility_modifier = new_agility_modifier;
}

int StatisticsModifier::get_agility_modifier() const
{
  return agility_modifier;
}

void StatisticsModifier::set_health_modifier(const int new_health_modifier)
{
  health_modifier = new_health_modifier;
}

int StatisticsModifier::get_health_modifier() const
{
  return health_modifier;
}

void StatisticsModifier::set_intelligence_modifier(const int new_intelligence_modifier)
{
  intelligence_modifier = new_intelligence_modifier;
}

int StatisticsModifier::get_intelligence_modifier() const
{
  return intelligence_modifier;
}

void StatisticsModifier::set_willpower_modifier(const int new_willpower_modifier)
{
  willpower_modifier = new_willpower_modifier;
}

int StatisticsModifier::get_willpower_modifier() const
{
  return willpower_modifier;
}

void StatisticsModifier::set_charisma_modifier(const int new_charisma_modifier)
{
  charisma_modifier = new_charisma_modifier;
}

int StatisticsModifier::get_charisma_modifier() const
{
  return charisma_modifier;
}

void StatisticsModifier::set_evade_modifier(const int new_evade_modifier)
{
  evade_modifier = new_evade_modifier;
}

int StatisticsModifier::get_evade_modifier() const
{
  return evade_modifier;
}

void StatisticsModifier::set_soak_modifier(const int new_soak_modifier)
{
  soak_modifier = new_soak_modifier;
}

int StatisticsModifier::get_soak_modifier() const
{
  return soak_modifier;
}

vector<int> StatisticsModifier::get_raw_values() const
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

bool StatisticsModifier::serialize(ostream& stream) const
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

  return true;
}

bool StatisticsModifier::deserialize(istream& stream)
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

  return true;
}

ClassIdentifier StatisticsModifier::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STATISTICS_MODIFIER;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatisticsModifier_test.cpp"
#endif