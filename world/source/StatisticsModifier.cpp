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
charisma_modifier(0)
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
charisma_modifier(new_charisma_modifier)
{
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

bool StatisticsModifier::serialize(ostream& stream) const
{
  Serialize::write_int(stream, strength_modifier);
  Serialize::write_int(stream, dexterity_modifier);
  Serialize::write_int(stream, agility_modifier);
  Serialize::write_int(stream, health_modifier);
  Serialize::write_int(stream, intelligence_modifier);
  Serialize::write_int(stream, willpower_modifier);
  Serialize::write_int(stream, charisma_modifier);


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

  return true;
}

ClassIdentifier StatisticsModifier::internal_class_identifier() const
{
  return CLASS_ID_STATISTICS_MODIFIER;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatisticsModifier_test.cpp"
#endif