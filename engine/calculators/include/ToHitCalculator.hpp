#pragma once
#include "AttackTypes.hpp"
#include "Map.hpp"

class ToHitCalculator
{
  public:
    ToHitCalculator();
    ToHitCalculator(const AttackType new_attack_type);
    virtual ~ToHitCalculator() = default;
    
    virtual int calculate(CreaturePtr creature, MapPtr map) = 0;
    virtual Statistic& get_statistic(CreaturePtr creature) = 0;
    
  protected:
    void init_skill_bonuses();

    virtual int get_level_bonus(CreaturePtr creature);
    virtual int get_weapon_bonus(CreaturePtr creature);
    virtual int get_modifier_bonus(CreaturePtr creature);
    virtual int get_skills_bonus(CreaturePtr creature);
    virtual int get_status_bonus(CreaturePtr creature);
    virtual int get_terrain_bonus(CreaturePtr creature, MapPtr current_map);

    SkillType get_terrain_lore_skill(CreaturePtr creature, MapPtr map);

    AttackType attack_type;

    static std::map<TileType, SkillType> tt_skill_bonuses;
    static std::map<MapType, SkillType> mt_skill_bonuses;

    static const int NWP_SKILL_BONUS_DIVISOR;
    static const int BLESS_STATUS_BONUS;
    static const int LORE_BONUS_DIVISOR;
};

using ToHitCalculatorPtr = std::unique_ptr<ToHitCalculator>;
