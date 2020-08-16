#pragma once
#include "Creature.hpp"

class NPCSkillDistributor
{
  public:
    void distribute_unused_skill_points(CreaturePtr creature);
    std::vector<SkillType> get_skills_to_improve(CreaturePtr creature) const;
};
