#include <sstream>
#include "Class.hpp"

using namespace std;

Class::Class()
: strength_modifier(0)
, dexterity_modifier(0)
, agility_modifier(0)
, health_modifier(0)
, intelligence_modifier(0)
, willpower_modifier(0)
, charisma_modifier(0)
, user_playable(false)
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

void Class::set_strength_modifier(const int new_strength_modifier)
{
  strength_modifier = new_strength_modifier;
}

int Class::get_strength_modifier() const
{
  return strength_modifier;
}

void Class::set_dexterity_modifier(const int new_dexterity_modifier)
{
  dexterity_modifier = new_dexterity_modifier;
}

int Class::get_dexterity_modifier() const
{
  return dexterity_modifier;
}

void Class::set_agility_modifier(const int new_agility_modifier)
{
  agility_modifier = new_agility_modifier;
}

int Class::get_agility_modifier() const
{
  return agility_modifier;
}

void Class::set_health_modifier(const int new_health_modifier)
{
  health_modifier = new_health_modifier;
}

int Class::get_health_modifier() const
{
  return health_modifier;
}

void Class::set_intelligence_modifier(const int new_intelligence_modifier)
{
  intelligence_modifier = new_intelligence_modifier;
}

int Class::get_intelligence_modifier() const
{
  return intelligence_modifier;
}

void Class::set_willpower_modifier(const int new_willpower_modifier)
{
  willpower_modifier = new_willpower_modifier;
}

int Class::get_willpower_modifier() const
{
  return willpower_modifier;
}

void Class::set_charisma_modifier(const int new_charisma_modifier)
{
  charisma_modifier = new_charisma_modifier;
}

int Class::get_charisma_modifier() const
{
  return charisma_modifier;
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
  class_details << strength_modifier << " " << dexterity_modifier << " " << agility_modifier << " " << health_modifier << " " << intelligence_modifier << " " << willpower_modifier << " " << charisma_modifier << endl;
  class_details << class_name_value << endl;
  class_details << class_abrv_value << endl;
  class_details << class_desc_value << endl;
  class_details << resistances.str() << endl;
  class_details << skills.str() << endl;
  class_details << experience_multiplier << endl;

  return class_details.str();
}
