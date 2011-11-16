#include "UpStaircaseTile.hpp"

StaircaseType UpStaircaseTile::get_staircase_type() const
{
  return STAIRCASE_UP;
}

#ifdef UNIT_TESTS
#include "unit_tests/UpStaircaseTile_test.cpp"
#endif
