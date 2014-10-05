#include "DisplayStatistics.hpp"

using namespace std;

DisplayStatistics::DisplayStatistics()
{
}

DisplayStatistics DisplayStatistics::create
(
  const string& new_name,
  const string& new_synopsis,
  const pair<string, Colour>& new_strength,
  const pair<string, Colour>& new_dexterity,
  const pair<string, Colour>& new_agility,
  const pair<string, Colour>& new_health,
  const pair<string, Colour>& new_intelligence,
  const pair<string, Colour>& new_willpower,
  const pair<string, Colour>& new_charisma,
  const string& new_speed,
  const string& new_level,
  const string& new_defence,
  const pair<string, Colour>& new_alignment,
  const string& new_hit_points,
  const string& new_arcana_points,
  const string& new_map_depth,
  const std::vector<std::pair<std::string, Colour>>& new_status_ailments
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
  ds.set_speed(new_speed);
  ds.set_level(new_level);
  ds.set_defence(new_defence);
  ds.set_alignment(new_alignment);
  ds.set_hit_points(new_hit_points);
  ds.set_arcana_points(new_arcana_points);
  ds.set_map_depth(new_map_depth);
  ds.set_status_ailments(new_status_ailments);

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

void DisplayStatistics::set_strength(const pair<string, Colour>& new_strength)
{
  strength = new_strength;
}

pair<string, Colour> DisplayStatistics::get_strength() const
{
  return strength;
}

void DisplayStatistics::set_dexterity(const pair<string, Colour>& new_dexterity)
{
  dexterity = new_dexterity;
}

pair<string, Colour> DisplayStatistics::get_dexterity() const
{
  return dexterity;
}

void DisplayStatistics::set_agility(const pair<string, Colour>& new_agility)
{
  agility = new_agility;
}

pair<string, Colour> DisplayStatistics::get_agility() const
{
  return agility;
}

void DisplayStatistics::set_health(const pair<string, Colour>& new_health)
{
  health = new_health;
}

pair<string, Colour> DisplayStatistics::get_health() const
{
  return health;
}

void DisplayStatistics::set_intelligence(const pair<string, Colour>& new_intelligence)
{
  intelligence = new_intelligence;
}

pair<string, Colour> DisplayStatistics::get_intelligence() const
{
  return intelligence;
}

void DisplayStatistics::set_willpower(const pair<string, Colour>& new_willpower)
{
  willpower = new_willpower;
}

pair<string, Colour> DisplayStatistics::get_willpower() const
{
  return willpower;
}

void DisplayStatistics::set_charisma(const pair<string, Colour>& new_charisma)
{
  charisma = new_charisma;
}

pair<string, Colour> DisplayStatistics::get_charisma() const
{
  return charisma;
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

void DisplayStatistics::set_alignment(const pair<string, Colour>& new_alignment)
{
  alignment = new_alignment;
}

string DisplayStatistics::get_defence() const
{
  return defence;
}

pair<string, Colour> DisplayStatistics::get_alignment() const
{
  return alignment;
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

void DisplayStatistics::set_status_ailments(const std::vector<std::pair<std::string, Colour>>& new_status_ailments)
{
  status_ailments = new_status_ailments;
}

std::vector<std::pair<std::string, Colour>> DisplayStatistics::get_status_ailments() const
{
  return status_ailments;
}