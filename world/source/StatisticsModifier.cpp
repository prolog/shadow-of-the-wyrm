#include "StatisticsModifier.hpp"

// Default all the modifiers to 0.
StatisticsModifier::StatisticsModifier()
: strength_modifier(0),
dexterity_modifier(0),
agility_modifier(0),
health_modifier(0),
intelligence_modifier(0),
willpower_modifier(0),
charisma_modifier(0),
valour_modifier(0),
spirit_modifier(0)
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
  const int new_charisma_modifier,
  const int new_valour_modifier,
  const int new_spirit_modifier
)
: strength_modifier(new_strength_modifier),
dexterity_modifier(new_dexterity_modifier),
agility_modifier(new_agility_modifier),
health_modifier(new_health_modifier),
intelligence_modifier(new_intelligence_modifier),
willpower_modifier(new_willpower_modifier),
charisma_modifier(new_charisma_modifier),
valour_modifier(new_valour_modifier),
spirit_modifier(new_spirit_modifier)
{
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

void StatisticsModifier::set_valour_modifier(const int new_valour_modifier)
{
  valour_modifier = new_valour_modifier;
}

int StatisticsModifier::get_valour_modifier() const
{
  return valour_modifier;
}

void StatisticsModifier::set_spirit_modifier(const int new_spirit_modifier)
{
  spirit_modifier = new_spirit_modifier;
}

int StatisticsModifier::get_spirit_modifier() const
{
  return spirit_modifier;
}

