#include "DownStaircaseTile.hpp"

StaircaseType DownStaircaseTile::get_staircase_type() const
{
  return STAIRCASE_DOWN;
}

#ifdef UNIT_TESTS
#include "unit_tests/DownStaircaseTile_test.cpp"
#endif
