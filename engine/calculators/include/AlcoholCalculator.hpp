#pragma once
#include "common.hpp"
#include "Consumable.hpp"
#include "Creature.hpp"

class AlcoholCalculator
{
  public:
    AlcoholCalculator();

    bool is_immediately_sick(CreaturePtr creature, const float standard_drinks);

    uint calculate_minutes_for_absorption(CreaturePtr creature);
    uint calculate_minutes_for_metabolization(CreaturePtr creature);

    float calculate_grams_to_cancel(ConsumablePtr consumable);
    float calculate_grams_to_absorb(CreaturePtr creature);
    float calculate_grams_to_metabolize(CreaturePtr creature);

    bool is_drunk(CreaturePtr creature);
    bool is_dead_of_alcohol_poisoning(CreaturePtr creature);

  protected:
    void initialize_sex_based_maps();

    static const uint IMMEDIATE_SICKNESS_TOUGHNESS_DIVISOR;
    static const uint BASE_MINUTES_FOR_ABSORPTION;
    static const uint BASE_MINUTES_FOR_METABOLIZATION;
    static const float CANCEL_ALCOHOL_GRAMS_PER_OUNCE;
    static const float BASE_METABOLISM_RATE;
    static const float DRUNK_BAC_THRESHOLD;
    static const float DEAD_BAC_THRESHOLD;

    static std::map<CreatureSex, float> absorption_by_sex;
};

