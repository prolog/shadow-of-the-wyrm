#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class ReadCalculator
{
  public:
    ActionCostValue calculate_reading_acv(CreaturePtr creature);

  protected:
    static const int BASE_READING_ACV;
};

