#pragma once
#include "Creature.hpp"

// Calculator for tanning-related tasks.  Tanning creates armour, and
// because new armour is being created, there is a chance that it is
// better than average, or even truly exceptional.
class TanningCalculator
{
  public:
    int calculate_evade_bonus(CreaturePtr creature);
    int calculate_soak_bonus(CreaturePtr creature);

    Resistances calculate_item_resistances(CreaturePtr creature, const Resistances& skin_resistances);

  protected:
    friend class TanningCalculatorTestFixture;

    std::vector<int> calculate_evade_probabilities(CreaturePtr creature);
    std::vector<int> calculate_soak_probabilities(CreaturePtr creature);

    double calculate_resistance_value(CreaturePtr creature, ResistancePtr resist);
    int calculate_potential_extra_resistance_points(CreaturePtr creature);
    
    static const int MAX_EVADE_BONUS;
    static const int MAX_SOAK_BONUS;
    static const int TANNING_EVADE_DECREMENT;
    static const int TANNING_SOAK_DECREMENT;
    static const int BASE_IMPROVEMENT_PCT;
    static const int MAX_IMPROVEMENT_PCT;
    static const int BASE_RESIST_DIVISOR;
    static const int PCT_CHANCE_EXTRA_POINT;

    static const std::vector<std::pair<int, double>> SKILL_VALUE_DIVISORS;
};

