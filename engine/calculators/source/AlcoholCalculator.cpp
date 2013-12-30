#include "AlcoholCalculator.hpp"

const uint AlcoholCalculator::BASE_MINUTES_FOR_ABSORPTION = 30;
const uint AlcoholCalculator::BASE_MINUTES_FOR_METABOLIZATION = 60;

uint AlcoholCalculator::calculate_minutes_for_absorption(CreaturePtr creature)
{
  return BASE_MINUTES_FOR_ABSORPTION;
}

uint AlcoholCalculator::calculate_minutes_for_metabolization(CreaturePtr creature)
{
  return BASE_MINUTES_FOR_METABOLIZATION;
}

