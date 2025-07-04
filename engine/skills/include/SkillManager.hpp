#pragma once
#include "Creature.hpp"

class SkillManager
{
  public:
    // Do a percentile check against a particular NWP, weapon, or magic skill.
    // Mark the skill based on the result.
    bool check_skill(CreaturePtr creature, const SkillType skill_type, const int num_checks = 1);
    
    // Get the value for a particular NWP, weapon, or magic skill
    int get_skill_value(CreaturePtr creature, const SkillType skill_type);

    // Mark a particular NWP, weapon, or magic skill
    void mark_skill(CreaturePtr creature, const SkillType skill_type, const bool skill_check_result);
    void mark_skill_with_probability(const int pct_chance, CreaturePtr creature, const SkillType skill_type, const bool skill_check_result);

  protected:
    static const int PERCENT_CHANCE_TO_MARK_SKILL_ON_FAILURE;
};
