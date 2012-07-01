#pragma once
#include "Creature.hpp"

class SkillManager
{
  public:
    // Get the value for a particular NWP, weapon, or magic skill
    int get_skill_value(CreaturePtr creature, const SkillType skill_type);

    // Mark a particular NWP, weapon, or magic skill
    void mark_skill(CreaturePtr creature, const SkillType skill_type);
};
