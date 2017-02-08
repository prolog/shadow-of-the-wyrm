#pragma once
#include "Creature.hpp"
#include "SkillTypes.hpp"

// Used for creating new items from a particular skill - Bowyer or Fletchery,
// currently.
class CreateItemCalculator
{
  public:
    int calc_potential_improvement_points(CreaturePtr creature, const SkillType create_skill);

  protected:
    static const int PRIMARY_SKILL_DIVISOR;
    static const int CRAFTING_SKILL_DIVISOR;
};

