#include "FenceCalculator.hpp"

const int FenceCalculator::PCT_CHANCE_BOARD = 25;

int FenceCalculator::calc_pct_chance_break(CreaturePtr creature) const
{
  int chance_break = 0;

  if (creature != nullptr)
  {
    chance_break = std::min<int>(100, creature->get_strength().get_current() * 2);
  }

  return chance_break;
}

int FenceCalculator::calc_pct_chance_board(CreaturePtr creature) const
{
  int chance_board = 0;

  if (creature != nullptr)
  {
    chance_board = PCT_CHANCE_BOARD;
  }

  return chance_board;
}

#ifdef UNIT_TESTS
#include "unit_tests/FenceCalculator_test.cpp"
#endif
