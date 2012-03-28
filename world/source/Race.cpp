#include <sstream>
#include "Race.hpp"
#include "StringTable.hpp"

using namespace std;

Race::Race()
{
  // Initialize primitive types.  Statistics will already be initialized via their class.
  experience_multiplier = 1.0;
  user_playable = false;
  valour_modifier = 0;
  spirit_modifier = 0;
  size = CREATURE_SIZE_MEDIUM;
}

Race::~Race()
{
}

bool Race::operator< (const Race& race)
{
  return get_race_id() < race.get_race_id();
}

void Race::set_race_id(const string& internal_race_id)
{
  race_id = internal_race_id;
}

string Race::get_race_id() const
{
  return race_id;
}

void Race::set_user_playable(const bool playable)
{
  user_playable = playable;
}

bool Race::get_user_playable() const
{
  return user_playable;
}

void Race::set_race_name_sid(const string& race_sid)
{
  race_name_sid = race_sid;
}

string Race::get_race_name_sid() const
{
  return race_name_sid;
}

void Race::set_race_short_description_sid(const string& race_short_desc_sid)
{
  race_short_description_sid = race_short_desc_sid;
}

string Race::get_race_short_description_sid() const
{
  return race_short_description_sid;
}

void Race::set_race_description_sid(const string& race_desc_sid)
{
  race_description_sid = race_desc_sid;
}

string Race::get_race_description_sid() const
{
  return race_description_sid;
}

void Race::set_race_abbreviation_sid(const string& race_abrv_sid)
{
  race_abbreviation_sid = race_abrv_sid;
}

string Race::get_race_abbreviation_sid() const
{
  return race_abbreviation_sid;
}

void Race::set_size(const CreatureSize new_size)
{
  size = new_size;
}

CreatureSize Race::get_size() const
{
  return size;
}

void Race::set_age_info(const AgeInfo& new_age_info)
{
  age_info = new_age_info;
}

AgeInfo Race::get_age_info() const
{
  return age_info;
}

void Race::set_starting_strength(const Statistic& new_starting_strength)
{
  starting_strength = new_starting_strength;
}

Statistic Race::get_starting_strength() const
{
  return starting_strength;
}

void Race::set_starting_dexterity(const Statistic& new_starting_dexterity)
{
  starting_dexterity = new_starting_dexterity;
}

Statistic Race::get_starting_dexterity() const
{
  return starting_dexterity;
}

void Race::set_starting_agility(const Statistic& new_starting_agility)
{
  starting_agility = new_starting_agility;
}

Statistic Race::get_starting_agility() const
{
  return starting_agility;
}

void Race::set_starting_health(const Statistic& new_starting_health)
{
  starting_health = new_starting_health;
}

Statistic Race::get_starting_health() const
{
  return starting_health;
}

void Race::set_starting_intelligence(const Statistic& new_starting_intelligence)
{
  starting_intelligence = new_starting_intelligence;
}

Statistic Race::get_starting_intelligence() const
{
  return starting_intelligence;
}

void Race::set_starting_willpower(const Statistic& new_starting_willpower)
{
  starting_willpower = new_starting_willpower;
}

Statistic Race::get_starting_willpower() const
{
  return starting_willpower;
}

void Race::set_starting_charisma(const Statistic& new_starting_charisma)
{
  starting_charisma = new_starting_charisma;
}

Statistic Race::get_starting_charisma() const
{
  return starting_charisma;
}

void Race::set_valour_modifier(const int new_valour_modifier)
{
  valour_modifier = new_valour_modifier;
}

int Race::get_valour_modifier() const
{
  return valour_modifier;
}

void Race::set_spirit_modifier(const int new_spirit_modifier)
{
  spirit_modifier = new_spirit_modifier;
}

int Race::get_spirit_modifier() const
{
  return spirit_modifier;
}

void Race::set_starting_speed(const Statistic& new_starting_speed)
{
  starting_speed = new_starting_speed;
}

Statistic Race::get_starting_speed() const
{
  return starting_speed;
}

void Race::set_experience_multiplier(const float new_experience_multiplier)
{
  experience_multiplier = new_experience_multiplier;
}

float Race::get_experience_multiplier() const
{
  return experience_multiplier;
}

void Race::set_initial_deity_ids(const std::vector<std::string>& new_initial_deity_ids)
{
  initial_deity_ids = new_initial_deity_ids;
}

std::vector<std::string> Race::get_initial_deity_ids() const
{
  return initial_deity_ids;
}

void Race::set_resistances(const Resistances& new_resists)
{
  resistances = new_resists;
}

Resistances Race::get_resistances() const
{
  return resistances;
}

void Race::set_skills(const Skills& new_skills)
{
  skills = new_skills;
}

Skills Race::get_skills() const
{
  return skills;
}

// Shouldn't be used in game - just used by the stub tester to ensure everything looks okay.
string Race::str() const
{
  ostringstream race_details;

  string race_name_value = StringTable::get(race_name_sid);
  string race_desc_value = StringTable::get(race_description_sid);
  string race_abrv_value = StringTable::get(race_abbreviation_sid);

  race_details << race_id << endl;
  race_details << starting_strength.get_base() << " " << starting_dexterity.get_base() << " " << starting_agility.get_base() << " " << starting_health.get_base() << " " << starting_intelligence.get_base() << " " << starting_willpower.get_base() << " " << starting_charisma.get_base() << " " << starting_speed.get_base() << endl;
  race_details << valour_modifier << " " << spirit_modifier << endl;
  race_details << race_name_value << endl;
  race_details << race_abrv_value << endl;
  race_details << race_desc_value << endl;
  race_details << resistances.str() << endl;
  race_details << skills.str() << endl;
  race_details << size << endl;
  race_details << experience_multiplier << endl;

  return race_details.str();
}

#ifdef UNIT_TESTS
#include "unit_tests/Race_test.cpp"
#endif
