#pragma once
#include "Creature.hpp"

// Calculator for tanning-related tasks.  Tanning creates armour, and
// because new armour is being created, there is a chance that it is
// better than average, or even truly exceptional.
class TanningCalculator
{
  public:
    int calculate_value_bonus(const int bonus_pts);

    int calculate_combat_bonus_min(CreaturePtr creature);
    int calculate_combat_bonus_max(CreaturePtr creature);

    int calculate_evade_bonus_min(CreaturePtr creature);
    int calculate_evade_bonus_max(CreaturePtr creature);
    int calculate_soak_bonus_min(CreaturePtr creature);
    int calculate_soak_bonus_max(CreaturePtr creature);

    Resistances calculate_item_resistances(CreaturePtr creature, const Resistances& skin_resistances);

  protected:
    friend class TanningCalculatorTestFixture;

    std::vector<int> calculate_combat_probabilities(CreaturePtr creature);
    std::vector<int> calculate_evade_probabilities(CreaturePtr creature);
    std::vector<int> calculate_soak_probabilities(CreaturePtr creature);

    double calculate_resistance_value(CreaturePtr creature, const Resistance& resist);
    int calculate_potential_extra_resistance_points(CreaturePtr creature);
    
    int calculate_skills_bonus(CreaturePtr creature, const int divisor);

    static const int COMBAT_MIN_DIVISOR;
    static const int COMBAT_MAX_DIVISOR;
    static const int EVADE_MIN_DIVISOR;
    static const int EVADE_MAX_DIVISOR;
    static const int SOAK_MIN_DIVISOR;
    static const int SOAK_MAX_DIVISOR;
    static const int BASE_IMPROVEMENT_PCT;
    static const int MAX_IMPROVEMENT_PCT;
    static const int BASE_RESIST_DIVISOR;
    static const int PCT_CHANCE_EXTRA_POINT;
    static const int VALUE_BONUS_MULTIPLIER;

    static const std::vector<std::pair<int, double>> SKILL_VALUE_DIVISORS;
};

