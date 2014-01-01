#pragma once
#include "common.hpp"
#include "Creature.hpp"

class AlcoholCalculator
{
  public:
    AlcoholCalculator();

    uint calculate_minutes_for_absorption(CreaturePtr creature);
    uint calculate_minutes_for_metabolization(CreaturePtr creature);

    float calculate_grams_to_absorb(CreaturePtr creature);
    float calculate_grams_to_metabolize(CreaturePtr creature);

    bool is_drunk(CreaturePtr creature);

  protected:
    void initialize_sex_based_maps();

    static const uint BASE_MINUTES_FOR_ABSORPTION;
    static const uint BASE_MINUTES_FOR_METABOLIZATION;
    static const float BASE_METABOLISM_RATE;
    static const float DRUNK_BAC_THRESHOLD;

    static std::map<CreatureSex, float> absorption_by_sex;
};

