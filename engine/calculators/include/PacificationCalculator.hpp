#pragma once
#include "Creature.hpp"

class PacificationCalculator
{
  public:
    int calculate_pct_chance_pacify_music(CreaturePtr music_cr, CreaturePtr fov_cr, const bool charms_creature, const ItemStatus item_status) const;
    int calculate_pct_chance_tame_beastmastery(CreaturePtr taming_creature, CreaturePtr tamed_creature);
    double calculate_exp_proportion(CreaturePtr taming_creature, const SkillType skill);

  protected:
    int get_item_status_bonus(const ItemStatus item_status) const;

    static const int MAX_PCT_CHANCE_PACIFY_MUSIC;
    static const int MAX_PCT_CHANCE_TAME_BEASTMASTERY;
    static const int CHARMS_BONUS;
};

