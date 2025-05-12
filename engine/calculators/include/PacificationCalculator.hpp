#pragma once
#include "Creature.hpp"

class PacificationCalculator
{
  public:
    int calculate_pct_chance_pacify_music(CreaturePtr music_cr, CreaturePtr fov_cr, const bool charms_creature, const ItemStatus item_status) const;
    int calculate_pct_chance_tame_beastmastery(CreaturePtr taming_creature, CreaturePtr tamed_creature);
    double calculate_exp_proportion(CreaturePtr taming_creature, const SkillType skill);
    double calculate_exp_proportion_follower_kill(CreaturePtr leader);
    Damage calculate_follower_damage_bonus(CreaturePtr leader);

  protected:
    int get_item_status_bonus(const ItemStatus item_status) const;

    static const int MAX_PCT_CHANCE_PACIFY_MUSIC;
    static const int MAX_PCT_CHANCE_TAME_BEASTMASTERY;
    static const int CHARMS_BONUS;
    static const int BASE_EXP_PROPORTION_LEADERSHIP;
    static const int LEADERSHIP_EXP_DIVISOR;
    static const int LEADERSHIP_DAMAGE_DIVISOR;
    static const int PCT_CHANCE_PACIFY_MUSIC_ENRAGED;
    static const int PCT_CHANCE_PACIFY_BEASTMASTERY_ENRAGED;
};

