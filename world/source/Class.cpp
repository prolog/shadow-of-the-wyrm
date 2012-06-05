#include <sstream>
#include "Class.hpp"

using namespace std;

Class::Class()
: user_playable(false)
, hit_dice(1)
, ap_dice(0)
{
}

Class::~Class()
{
}

void Class::set_class_id(const string& id)
{
  class_id = id;
}

string Class::get_class_id() const
{
  return class_id;
}

void Class::set_class_name_sid(const string& new_class_name)
{
  class_name_sid = new_class_name;
}

string Class::get_class_name_sid() const
{
  return class_name_sid;
}

void Class::set_class_description_sid(const string& new_class_description_sid)
{
  class_description_sid = new_class_description_sid;
}

string Class::get_class_description_sid() const
{
  return class_description_sid;
}

void Class::set_class_abbreviation_sid(const string& new_class_abbreviation_sid)
{
  class_abbreviation_sid = new_class_abbreviation_sid;
}

string Class::get_class_abbreviation_sid() const
{
  return class_abbreviation_sid;
}

void Class::set_starting_valour(const Statistic& new_valour)
{
  starting_valour = new_valour;
}

Statistic Class::get_starting_valour() const
{
  return starting_valour;
}

void Class::set_starting_spirit(const Statistic& new_spirit)
{
  starting_spirit = new_spirit;
}

Statistic Class::get_starting_spirit() const
{
  return starting_spirit;
}

void Class::set_statistics_modifier(const StatisticsModifier& new_statistics_modifier)
{
  statistics_modifier = new_statistics_modifier;
}

StatisticsModifier Class::get_statistics_modifier() const
{
  return statistics_modifier;
}

void Class::set_resistances(const Resistances& new_resistances)
{
  resistances = new_resistances;
}

Resistances Class::get_resistances() const
{
  return resistances;
}

void Class::set_skills(const Skills& new_skills)
{
  skills = new_skills;
}

Skills Class::get_skills() const
{
  return skills;
}

void Class::set_user_playable(const bool playable)
{
  user_playable = playable;
}

bool Class::get_user_playable() const
{
  return user_playable;
}

void Class::set_experience_multiplier(const float new_multiplier)
{
  experience_multiplier = new_multiplier;
}

float Class::get_experience_multiplier() const
{
  return experience_multiplier;
}

void Class::set_hit_dice(const uint new_hit_dice)
{
  hit_dice = new_hit_dice;
}

uint Class::get_hit_dice() const
{
  return hit_dice;
}

void Class::set_ap_dice(const uint new_ap_dice)
{
  ap_dice = new_ap_dice;
}

uint Class::get_ap_dice() const
{
  return ap_dice;
}

string Class::str() const
{
  ostringstream class_details;

  string class_name_value = StringTable::get(class_name_sid);
  string class_desc_value = StringTable::get(class_description_sid);
  string class_abrv_value = StringTable::get(class_abbreviation_sid);

  class_details << class_id << endl;
  class_details << hit_dice << " " << ap_dice << endl;
  class_details << starting_valour.get_base() << " " << starting_spirit.get_base() << endl;
  class_details << statistics_modifier.get_strength_modifier() << " " 
                << statistics_modifier.get_dexterity_modifier() << " " 
                << statistics_modifier.get_agility_modifier() << " " 
                << statistics_modifier.get_health_modifier() << " "
                << statistics_modifier.get_intelligence_modifier() << " " 
                << statistics_modifier.get_willpower_modifier() << " " 
                << statistics_modifier.get_charisma_modifier() 
                << endl;
  class_details << class_name_value << endl;
  class_details << class_abrv_value << endl;
  class_details << class_desc_value << endl;
  class_details << resistances.str() << endl;
  class_details << skills.str() << endl;
  class_details << experience_multiplier << endl;

  return class_details.str();
}
