#include "DisplayStatistics.hpp"

using namespace std;

DisplayStatistics::DisplayStatistics()
{
}

DisplayStatistics DisplayStatistics::create
(
  const string& new_name,
  const string& new_strength,
  const string& new_dexterity,
  const string& new_agility,
  const string& new_health,
  const string& new_intelligence,
  const string& new_willpower,
  const string& new_charisma
)
{
  DisplayStatistics ds;

  ds.set_name(new_name);
  ds.set_strength(new_strength);
  ds.set_dexterity(new_dexterity);
  ds.set_agility(new_agility);
  ds.set_health(new_health);
  ds.set_intelligence(new_intelligence);
  ds.set_willpower(new_willpower);
  ds.set_charisma(new_charisma);

  return ds;
}

void DisplayStatistics::set_name(const string& new_name)
{
  name = new_name;
}

string DisplayStatistics::get_name() const
{
  return name;
}

void DisplayStatistics::set_strength(const string& new_strength)
{
  strength = new_strength;
}

string DisplayStatistics::get_strength() const
{
  return strength;
}

void DisplayStatistics::set_dexterity(const string& new_dexterity)
{
  dexterity = new_dexterity;
}

string DisplayStatistics::get_dexterity() const
{
  return dexterity;
}

void DisplayStatistics::set_agility(const string& new_agility)
{
  agility = new_agility;
}

string DisplayStatistics::get_agility() const
{
  return agility;
}

void DisplayStatistics::set_health(const string& new_health)
{
  health = new_health;
}

string DisplayStatistics::get_health() const
{
  return health;
}

void DisplayStatistics::set_intelligence(const string& new_intelligence)
{
  intelligence = new_intelligence;
}

string DisplayStatistics::get_intelligence() const
{
  return intelligence;
}

void DisplayStatistics::set_willpower(const string& new_willpower)
{
  willpower = new_willpower;
}

string DisplayStatistics::get_willpower() const
{
  return willpower;
}

void DisplayStatistics::set_charisma(const string& new_charisma)
{
  charisma = new_charisma;
}

string DisplayStatistics::get_charisma() const
{
  return charisma;
}
