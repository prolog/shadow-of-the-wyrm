#pragma once
#include "Race.hpp"
#include "Class.hpp"

class Creature;
class Skills;

class SkillsCalculator
{
  public:
    static Skills calculate_skills(Race* race, Class* char_class);
    static int calculate_hidden_treasure_total_skill_value(CreaturePtr creature, const MapType map_type, const int lore_val);

  protected:
    SkillsCalculator();
    ~SkillsCalculator();

    static Skills calculate_general_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_melee_weapon_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_ranged_weapon_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_magic_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_skills_in_given_range(Race* race, Class* char_class, const Skills& current_skills, const int first_skill, const int last_skill);

    static const int HIDDEN_TREASURE_DUNGEONEERING_DIVISOR;
};
