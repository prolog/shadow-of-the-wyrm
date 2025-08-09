#pragma once
#include "Race.hpp"
#include "Class.hpp"

class Creature;
class Skills;

class SkillsCalculator
{
  public:
    SkillsCalculator();

    static Skills calculate_skills(Race* race, Class* char_class);
    static int calculate_hidden_treasure_total_skill_value(CreaturePtr creature, const MapType map_type, const int lore_val);

    virtual int get_terrain_to_hit_bonus(CreaturePtr creature, MapPtr current_map) const;
    virtual int get_terrain_damage_bonus(CreaturePtr creature, MapPtr current_map) const;

  protected:
    void init_skill_bonuses();

    virtual int get_terrain_bonus(CreaturePtr creature, MapPtr map, const int divisor) const;

    static Skills calculate_general_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_melee_weapon_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_ranged_weapon_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_magic_skills(Race* race, Class* char_class, const Skills& current_skills);
    static Skills calculate_skills_in_given_range(Race* race, Class* char_class, const Skills& current_skills, const int first_skill, const int last_skill);

    SkillType get_terrain_lore_skill(CreaturePtr creature, MapPtr map) const;

    static std::map<TileType, SkillType> tt_skill_bonuses;
    static std::map<MapType, SkillType> mt_skill_bonuses;

    static const int HIDDEN_TREASURE_DUNGEONEERING_DIVISOR;
    static const int LORE_TO_HIT_DIVISOR;
    static const int LORE_DAMAGE_DIVISOR;
};
