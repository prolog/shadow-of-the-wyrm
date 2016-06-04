#include <sstream>
#include "Conversion.hpp"
#include "SkillsDumper.hpp"
#include "SkillTextKeys.hpp"
using namespace std;

SkillsDumper::SkillsDumper(CreaturePtr new_creature, const uint new_num_cols)
: creature(new_creature), num_cols(new_num_cols)
{
}

SkillsDumper::~SkillsDumper()
{
}

string SkillsDumper::str() const
{
  return get_skills();
}

string SkillsDumper::get_skills() const
{
  ostringstream ss;

  ss << String::centre(get_skill_improvement_points_remaining_header(), num_cols) << " " << creature->get_skill_points() << endl << endl;
  
  ss << String::centre(get_general_skills_header(), num_cols)  << endl << endl;
  ss << get_general_skills() << endl << endl;
  
  ss << String::centre(get_weapon_skills_header(), num_cols) << endl << endl;
  ss << get_melee_weapon_skills() << endl << endl;
  
  ss << String::centre(get_ranged_weapon_skills_header(), num_cols) << endl << endl;
  ss << get_ranged_weapon_skills() << endl << endl;

  ss << String::centre(get_magical_skills_header(), num_cols) << endl << endl;
  ss << get_magical_skills() << endl << endl;
  
  return ss.str();
}

string SkillsDumper::get_general_skills_header() const
{
  string skills_header = StringTable::get(SkillTextKeys::SKILLS_GENERAL);
  return skills_header;
}

string SkillsDumper::get_general_skills() const
{
  string general_skills = get_skills_by_category(SkillCategory::SKILL_CATEGORY_GENERAL);
  return general_skills;
}

string SkillsDumper::get_skills_by_category(const SkillCategory category) const
{
  ostringstream ss;
  bool at_least_one_skill = false;
  
  if (creature)
  {
    SkillMap& skills = creature->get_skills().get_raw_skills_ref();
    
    for (SkillMap::const_iterator sk_it = skills.begin(); sk_it != skills.end(); sk_it++)
    {
      SkillPtr skill = sk_it->second;
      
      SkillCategory skill_category = skill->get_category();
      
      if (skill_category == category)
      {
        int skill_value = skill->get_value();
        
        if ((skill_value > 0) || skill->can_train_from_unlearned())
        {
          if (!at_least_one_skill) at_least_one_skill = true;
          ss << skill->str() << endl;
        }
      }
    }
  }
  
  if (!at_least_one_skill)
  {
    ss << String::centre("-", num_cols);
  }

  return ss.str();
}

string SkillsDumper::get_skill_improvement_points_remaining_header() const
{
  string sipr_header = StringTable::get(SkillTextKeys::SKILLS_IMPROVEMENT_POINTS_REMAINING);
  return sipr_header;
}

string SkillsDumper::get_weapon_skills_header() const
{
  string weapon_skills_header = StringTable::get(SkillTextKeys::SKILLS_WEAPON);
  return weapon_skills_header;
}

string SkillsDumper::get_melee_weapon_skills() const
{
  string melee_weapon_skills = get_skills_by_category(SkillCategory::SKILL_CATEGORY_MELEE);  
  return melee_weapon_skills;
}

string SkillsDumper::get_ranged_weapon_skills_header() const
{
  string ranged_weapon_skills_header = StringTable::get(SkillTextKeys::SKILLS_RANGED_WEAPON);
  return ranged_weapon_skills_header;
}

string SkillsDumper::get_ranged_weapon_skills() const
{
  string ranged_weapon_skills = get_skills_by_category(SkillCategory::SKILL_CATEGORY_RANGED);
  return ranged_weapon_skills;
}

string SkillsDumper::get_magical_skills_header() const
{
  string magical_skills_header = StringTable::get(SkillTextKeys::SKILLS_MAGIC);
  return magical_skills_header;
}

string SkillsDumper::get_magical_skills() const
{
  string magical_skills = get_skills_by_category(SkillCategory::SKILL_CATEGORY_MAGIC);
  return magical_skills;
}

