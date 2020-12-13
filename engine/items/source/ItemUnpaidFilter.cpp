#include <algorithm>
#include "ItemUnpaidFilter.hpp"

using namespace std;

ItemUnpaidFilter::ItemUnpaidFilter()
{
}

bool ItemUnpaidFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item)
  {
    passes = item->get_unpaid();
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemUnpaidFilter_test.cpp"
#endif
