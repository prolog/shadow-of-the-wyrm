#include "CalcUtils.hpp"

int CalcUtils::pct_val(const int pct)
{
  if (pct < 0) return 0;
  if (pct > 100) return 100;

  return pct;
}

#ifdef UNIT_TESTS
#include "unit_tests/CalcUtils_test.cpp"
#endif

