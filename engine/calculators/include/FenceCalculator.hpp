#pragma once
#include "Creature.hpp"

class FenceCalculator
{
  public:
    int calc_pct_chance_break(CreaturePtr creature) const;
    int calc_pct_chance_board(CreaturePtr creature) const;

  protected:
    static const int PCT_CHANCE_BOARD;
};
