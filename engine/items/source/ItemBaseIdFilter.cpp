#include "ItemBaseIdFilter.hpp"

using namespace std;

ItemBaseIdFilter::ItemBaseIdFilter(const string& new_base_id)
: base_id(new_base_id)
{
}

// The item passes the filter when the item:
// - Is non-null
// - Matches the material
bool ItemBaseIdFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item)
  {
    passes = (base_id == item->get_base_id());
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemBaseIdFilter_test.cpp"
#endif

