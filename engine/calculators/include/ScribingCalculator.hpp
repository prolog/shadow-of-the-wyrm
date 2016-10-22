#pragma once
#include "Creature.hpp"

class ScribingCalculator
{
  public:
    int calc_castings_per_scroll(CreaturePtr creature);

  protected:
    static const int MAX_CASTINGS_PER_SCROLL;
    static const int MIN_CASTINGS_PER_SCROLL;
    static const int SCRIBING_DIVISOR;
};