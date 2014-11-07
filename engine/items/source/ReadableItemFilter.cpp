#include "ReadableItemFilter.hpp"

// Check to see if the item is readable
bool ReadableItemFilter::passes_filter(ItemPtr item) const
{
  return (item && item->get_readable());
}

#ifdef UNIT_TESTS
#include "unit_tests/ReadableItemFilter_test.cpp"
#endif