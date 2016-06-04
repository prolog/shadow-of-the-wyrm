#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class SkillsDumper : public StringConverter
{
  public:
    SkillsDumper(CreaturePtr new_creature, const uint new_num_cols);
    ~SkillsDumper();
    
    std::string str() const override;

  protected:
    std::string get_skills() const;
    std::string get_skill_improvement_points_remaining_header() const;
    std::string get_general_skills_header() const;
    std::string get_general_skills() const;
    std::string get_weapon_skills_header() const;
    std::string get_melee_weapon_skills() const;
    std::string get_ranged_weapon_skills_header() const;
    std::string get_ranged_weapon_skills() const;
    std::string get_magical_skills_header() const;
    std::string get_magical_skills() const;
    std::string get_skills_by_category(const SkillCategory category) const;

    CreaturePtr creature;
    const int num_cols;
};
