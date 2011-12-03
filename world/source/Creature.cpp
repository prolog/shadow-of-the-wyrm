#include "Creature.hpp"

using namespace std;

// Set a reasonable set of default values for simple types, which are helpfully initialized to bullshit memory.
// Why did I write this in C++, again?
Creature::Creature()
: is_player(false)
, size( CREATURE_SIZE_MEDIUM )
// Everything else is a string, Statistic, etc.
{
}

void Creature::set_is_player(const bool player)
{
  is_player = player;
}

bool Creature::get_is_player() const
{
  return is_player;
}

void Creature::set_name(const string& new_name)
{
  name = new_name;
}

string Creature::get_name() const
{
  return name;
}

void Creature::set_age(const Statistic& new_age)
{
  age = new_age;
}

Statistic Creature::get_age() const
{
  return age;
}

void Creature::set_size(const CreatureSize& new_size)
{
  size = new_size;
}

CreatureSize Creature::get_size() const
{
  return size;
}

void Creature::set_strength(const Statistic& new_strength)
{
  strength = new_strength;
}

Statistic Creature::get_strength() const
{
  return strength;
}

void Creature::set_dexterity(const Statistic& new_dexterity)
{
  dexterity = new_dexterity;
}

Statistic Creature::get_dexterity() const
{
  return dexterity;
}

void Creature::set_agility(const Statistic& new_agility)
{
  agility = new_agility;
}

Statistic Creature::get_agility() const
{
  return agility;
}

void Creature::set_health(const Statistic& new_health)
{
  health = new_health;
}

Statistic Creature::get_health() const
{
  return health;
}

void Creature::set_intelligence(const Statistic& new_intelligence)
{
  intelligence = new_intelligence;
}

Statistic Creature::get_intelligence() const
{
  return intelligence;
}

void Creature::set_willpower(const Statistic& new_willpower)
{
  willpower = new_willpower;
}

Statistic Creature::get_willpower() const
{
  return willpower;
}

void Creature::set_charisma(const Statistic& new_charisma)
{
  charisma = new_charisma;
}

Statistic Creature::get_charisma() const
{
  return charisma;
}

void Creature::set_valour(const Statistic& new_valour)
{
  valour = new_valour;
}

Statistic Creature::get_valour() const
{
  return valour;
}

void Creature::set_spirit(const Statistic& new_spirit)
{
  spirit = new_spirit;
}

Statistic Creature::get_spirit() const
{
  return spirit;
}

void Creature::set_piety(const Statistic& new_piety)
{
  piety = new_piety;
}

Statistic Creature::get_piety() const
{
  return piety;
}

void Creature::set_speed(const Statistic& new_speed)
{
  speed = new_speed;
}

Statistic Creature::get_speed() const
{
  return speed;
}

void Creature::set_resistance_value(const ResistanceType resistance_type, double value)
{
  resistances.set_resistance_value(resistance_type, value);
}

void Creature::set_resistances(const Resistances& new_resistances)
{
  resistances = new_resistances;
}

Resistances& Creature::get_resistances()
{
  return resistances;
}

void Creature::set_skills(const Skills& new_skills)
{
  skills = new_skills;
}

Skills& Creature::get_skills()
{
  return skills;
}

void Creature::set_hit_points(const Statistic& new_hit_points)
{
  hit_points = new_hit_points;
}

void Creature::increment_hit_points(const int amount)
{
  hit_points.set_current(hit_points.get_current() + amount);
}

void Creature::decrement_hit_points(const int amount)
{
  hit_points.set_current(hit_points.get_current() - amount);
}

Statistic Creature::get_hit_points() const
{
  return hit_points;
}

void Creature::set_arcana_points(const Statistic& new_arcana_points)
{
  arcana_points = new_arcana_points;
}

void Creature::increment_arcana_points(const int amount)
{
  arcana_points.set_current(arcana_points.get_current() + amount);
}

void Creature::decrement_arcana_points(const int amount)
{
  arcana_points.set_current(arcana_points.get_current() - amount);
}

Statistic Creature::get_arcana_points() const
{
  return arcana_points;
}

void Creature::set_evade(const Statistic& new_evade)
{
  evade = new_evade;
}

Statistic Creature::get_evade() const
{
  return evade;
}

void Creature::set_soak(const Statistic& new_soak)
{
  soak = new_soak;
}

Statistic Creature::get_soak() const
{
  return soak;
}

#ifdef UNIT_TESTS
#include "unit_tests/Creature_test.cpp"
#endif
