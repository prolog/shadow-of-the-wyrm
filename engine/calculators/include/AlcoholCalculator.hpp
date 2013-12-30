#pragma once
#include "common.hpp"
#include "Creature.hpp"

class AlcoholCalculator
{
  public:
    uint calculate_minutes_for_absorption(CreaturePtr creature);
    uint calculate_minutes_for_metabolization(CreaturePtr creature);

    static const uint BASE_MINUTES_FOR_ABSORPTION;
    static const uint BASE_MINUTES_FOR_METABOLIZATION;
};

