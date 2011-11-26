#pragma once
#include "Race.hpp"
#include "Class.hpp"

class Creature;
class Skills;

class SkillsCalculator
{
  public:
    static Skills calculate_skills(const Creature& creature, RacePtr race, ClassPtr char_class);

  protected:
    SkillsCalculator();
    ~SkillsCalculator();

    static Skills calculate_general_skills(const Creature& creature, RacePtr race, ClassPtr char_class, const Skills& current_skills);

    static Skills calculate_melee_weapon_skills(const Creature& creature, RacePtr race, ClassPtr char_class, const Skills& current_skills);

    static Skills calculate_ranged_weapon_skills(const Creature& creature, RacePtr race, ClassPtr char_class, const Skills& current_skills);

    static Skills calculate_magic_skills(const Creature& creature, RacePtr race, ClassPtr char_class, const Skills& current_skills);

    static Skills calculate_skills_in_given_range(const Creature& creature, RacePtr race, ClassPtr char_class, const Skills& current_skills, const int first_skill, const int last_skill);
};
