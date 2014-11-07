#include "NullItemFilter.hpp"

bool NullFilter::passes_filter(ItemPtr item) const
{
  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullItemFilter_test.cpp"
#endif
