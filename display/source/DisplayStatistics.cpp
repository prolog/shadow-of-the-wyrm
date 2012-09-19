#include "DisplayStatistics.hpp"

using namespace std;

DisplayStatistics::DisplayStatistics()
{
}

DisplayStatistics DisplayStatistics::create
(
  const string& new_name,
  const string& new_synopsis,
  const string& new_strength,
  const string& new_dexterity,
  const string& new_agility,
  const string& new_health,
  const string& new_intelligence,
  const string& new_willpower,
  const string& new_charisma,
  const string& new_valour,
  const string& new_spirit,
  const string& new_speed,
  const string& new_level,
  const string& new_defence,
  const string& new_hit_points,
  const string& new_arcana_points,
  const string& new_map_depth
)
{
  DisplayStatistics ds;

  ds.set_name(new_name);
  ds.set_synopsis(new_synopsis);
  ds.set_strength(new_strength);
  ds.set_dexterity(new_dexterity);
  ds.set_agility(new_agility);
  ds.set_health(new_health);
  ds.set_intelligence(new_intelligence);
  ds.set_willpower(new_willpower);
  ds.set_charisma(new_charisma);
  ds.set_valour(new_valour);
  ds.set_spirit(new_spirit);
  ds.set_speed(new_speed);
  ds.set_level(new_level);
  ds.set_defence(new_defence);
  ds.set_hit_points(new_hit_points);
  ds.set_arcana_points(new_arcana_points);
  ds.set_map_depth(new_map_depth);

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

void DisplayStatistics::set_synopsis(const string& new_synopsis)
{
  synopsis = new_synopsis;
}

string DisplayStatistics::get_synopsis() const
{
  return synopsis;
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

void DisplayStatistics::set_valour(const string& new_valour)
{
  valour = new_valour;
}

string DisplayStatistics::get_valour() const
{
  return valour;
}

void DisplayStatistics::set_spirit(const string& new_spirit)
{
  spirit = new_spirit;
}

string DisplayStatistics::get_spirit() const
{
  return spirit;
}

void DisplayStatistics::set_speed(const string& new_speed)
{
  speed = new_speed;
}

string DisplayStatistics::get_speed() const
{
  return speed;
}

void DisplayStatistics::set_level(const string& new_level)
{
  level = new_level;
}

string DisplayStatistics::get_level() const
{
  return level;
}

void DisplayStatistics::set_defence(const string& new_defence)
{
  defence = new_defence;
}

string DisplayStatistics::get_defence() const
{
  return defence;
}

void DisplayStatistics::set_hit_points(const string& new_hit_points)
{
  hit_points = new_hit_points;
}

string DisplayStatistics::get_hit_points() const
{
  return hit_points;
}

void DisplayStatistics::set_arcana_points(const string& new_arcana_points)
{
  arcana_points = new_arcana_points;
}

string DisplayStatistics::get_arcana_points() const
{
  return arcana_points;
}

void DisplayStatistics::set_map_depth(const string& new_map_depth)
{
  map_depth = new_map_depth;
}

string DisplayStatistics::get_map_depth() const
{
  return map_depth;
}

