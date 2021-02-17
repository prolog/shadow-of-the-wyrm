#pragma once
#include "Creature.hpp"

class DivineCompanionCalculator
{
  public:
    Statistic calculate_hp(const Statistic& base_hp) const;
    Statistic calculate_ap(const Statistic& base_ap) const;
    int calculate_damage_modifier(CreaturePtr creature, const Damage& d) const;

  protected:
    static const double BASE_HP_MULT;
    static const double BASE_AP_MULT;
    static const int DAMAGE_MODIFIER_LEVEL_DIVISOR;
};

